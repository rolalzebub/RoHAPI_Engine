#include "SpriteCollider.h"
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"

namespace RoHAPI {
	SpriteCollider::~SpriteCollider()
	{
		if (mask != nullptr)
			delete[] mask;
	}

	void SpriteCollider::GenerateMask(BYTE* imageData, const Rect& rect)
	{
		if (mask != nullptr)
			delete[] mask;

		// How many DWORDs across do we need? 
		int numDwordsAcross = (rect.Width() + 31) / 32;

		// allocate	memory for the collision mask and clear
		DWORD* mask_ = new DWORD[numDwordsAcross * rect.Height()];
		memset(mask_, 0, numDwordsAcross * rect.Height() * 4);

		// Set up start pointers
		BYTE* sourcePntr = imageData;
		if (m_parentObject->HasComponent(AnimationC))
		{
			sourcePntr = m_parentObject->GetComponent<Animation>(AnimationC)->GetCurrentSprite();
		}
		DWORD* maskPointer = mask_;
		DWORD currentBit = 0;

		for (int y = 0; y < rect.Height(); y++)
		{
			for (int x = 0; x < rect.Width(); x++)
			{
				BYTE alpha = sourcePntr[3];

				// Each pixel can be represented as one bit, either 1 for solid or 0 for empty
				if (alpha > 0)
				{
					*maskPointer = *maskPointer | (1 << currentBit); // turn on the correct bit in the current mask DWORD
				}

				sourcePntr += 4;
				currentBit++;
				if (currentBit == 32)
				{
					// When we reach the last bit we move on to the next DWORD and reset bit to 0
					currentBit = 0;
					maskPointer++;
				}
			}
		}
		mask = mask_;
		m_rect = rect;
		dwordSize = numDwordsAcross;
	}

	bool SpriteCollider::CheckCollider(SharedPtr<SpriteCollider> collider)
	{
		Vec2i otherMaskSize = collider->GetMaskSize();

		int startX = 0;
		int startY = 0;
		int endX = maskSize.width;
		int endY = maskSize.height;

		for (int y = startY; y < endY; ++y)
		{
			for (int x = startX; x < endX; ++x)
			{
				//Offset of the current pixel for 4 BYTES (RGBA)
				int offset = ((y * maskSize.width) + x) * 4;
				int otherMaskOffset = ((y * otherMaskSize.width) + x) * 4;
				//Gets the alpha value from the images data by the offset for the alpha BYTE of the pixel
				BYTE alpha = (BYTE)mask[offset];

				//Coninue the next loop
				if (alpha == 0 && collider->GetMask()[otherMaskOffset] == 0)
					continue;
				else
				{
					return true;
				}
			}
		}
		return false;
	}
	void SpriteCollider::Start()
	{
		if (m_parentObject->HasComponent(AnimationC))
		{
			m_rect = Rect{(double) 0,(double)m_parentObject->GetComponent<Animation>(AnimationC)->GetIdvSpriteDims().y, (double)0, (double)m_parentObject->GetComponent<Animation>(AnimationC)->GetIdvSpriteDims().x };
			GenerateMask(m_parentObject->GetComponent<Animation>(AnimationC)->GetCurrentSprite(), m_rect);
		}

		else if (m_parentObject->HasComponent(SpriteC)) {
			m_rect = Rect{ 0, (double) m_parentObject->GetComponent<Sprite>(SpriteC)->GetSpriteDims().y, 0, (double) m_parentObject->GetComponent<Sprite>(SpriteC)->GetSpriteDims().x };
			GenerateMask(m_parentObject->GetComponent<Sprite>(SpriteC)->GetImage(), m_rect);
		}
	}
	void SpriteCollider::Update()
	{
	}
	Rect SpriteCollider::GetColliderRect() const
	{
		return m_rect;
	}
}