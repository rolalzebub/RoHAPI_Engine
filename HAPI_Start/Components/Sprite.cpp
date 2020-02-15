#include "Sprite.h"
namespace RoHAPI {
	Sprite::~Sprite()
	{
		if (imageData != nullptr) {}
			delete[] imageData;
	}

	void Sprite::Update()
	{
		
	}

	void Sprite::Stop()
	{
	}

	BYTE* Sprite::GetImage()
	{
		return imageData;
	}

	Vec2i Sprite::GetSpriteDims()
	{
		return spriteDims;
	}

	bool Sprite::CreateColouredBlock(Vec2i dimensions, HAPI_TColour colour)
	{
		if (imageData != nullptr)
			return false;

		imageData = (BYTE*) malloc(sizeof(HAPI_TColour) * dimensions.x * dimensions.y);

		memcpy(imageData, &colour, sizeof(HAPI_TColour));

		BYTE* tempPtr = imageData;
		tempPtr += 4;
		for (int i = 1; i < dimensions.x * dimensions.y; i++) {
			memcpy(tempPtr, &colour, sizeof(HAPI_TColour));
			tempPtr += 4;
		}

		spriteDims = dimensions;

		return true;
	}

	void Sprite::Renderable(bool canBeRendered)
	{
	}

	bool Sprite::Renderable() const
	{
		return false;
	}

	void Sprite::ID(const int id_)
	{
	}

	int Sprite::ID() const
	{
		return 0;
	}

	void Sprite::Name(const std::string& path)
	{
	}

	bool Sprite::LoadSprite(std::string path)
	{
		if (!HAPI.LoadTexture(path, &imageData, spriteDims.width, spriteDims.height))
		{
			HAPI.UserMessage("Error! Unable to load sprite!" + path, "RoHAPI Engine");
			return false;
		}
		return true;
	}
}