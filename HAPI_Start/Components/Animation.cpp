#include "Animation.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Spritesheet.h"
#include "Sprite.h"
namespace RoHAPI {
	Animation::~Animation() {
		
	}

	bool Animation::SetAnimation(std::string animName)
	{
		if (!clips.empty()) {
			if (clips.find(animName) != clips.end()) {
				currentAnimation = animName;
			}
		}
		
		currentSprite = 0;
		currentAnimationStart = 0;
		currentAnimationEnd = clips[currentAnimation].boundary_TexUV.width / m_spritesheet->GetIdvSpriteDims().x;
		return true;
	}

	void Animation::Start()
	{
		id = AnimationC;
		if(!clips.empty() && currentAnimation == "")
			currentAnimation = clips.begin()->second.animationName;
	}

	void Animation::Update()
	{
		if (enabled)
			Animate();
	}

	void Animation::AddAnimationClip(AnimationClip newAnim)
	{
		if (clips.find(newAnim.animationName) == clips.end())
		{
			clips[newAnim.animationName] = newAnim;
		}
	}

	void Animation::SetSpritesheet(Spritesheet* spritesheet)
	{
		//assign spritesheet to pick anim clips from
		m_spritesheet = spritesheet;
	}

	BYTE* Animation::GetCurrentSprite() const
	{
		BYTE* tempPtr = m_spritesheet->GetImage();

		tempPtr += ((clips.at(currentAnimation).start_TexUV.y) * m_spritesheet->GetSpriteDims().width) * 4;										//push pointer vertically down the spritesheet
		tempPtr += (clips.at(currentAnimation).start_TexUV.x + (currentSprite * m_spritesheet->GetIdvSpriteDims().x)) * 4;						//push pointer horizontally across the spritesheet

		return tempPtr;																								//return pointer at the top_left of the exact sprite to be rendered in the clip
	}

	Rect Animation::GetBoundingBox()
	{
		//Get bounding box for full animation clip on the spritesheet
		Rect box{ (double)clips[currentAnimation].start_TexUV.y, (double)clips[currentAnimation].boundary_TexUV.y, (double)clips[currentAnimation].start_TexUV.x, (double)clips[currentAnimation].boundary_TexUV.x };
		return box;
	}


	void Animation::Animate()
	{

		if ((Time.CurrentTime() - frameUpdateTime) / 1000.0 > frameDelay)
		{
			currentSprite++;
			frameUpdateTime = Time.CurrentTime();
		}

		if (currentSprite < currentAnimationStart)
			currentSprite = currentAnimationStart;
		if (currentSprite == currentAnimationEnd)
		{
			if (looping)
				currentSprite = currentAnimationStart;
			else
			{
				currentSprite = currentAnimationStart;
				return;
			}
		}

	}
}