#include "Spritesheet.h"
#include "GameObject.h"
#include "Animation.h"
namespace RoHAPI {
	Spritesheet::~Spritesheet()
	{
		if (imageData != nullptr)
			delete[] imageData;
	}

	const Vec2i Spritesheet::GetIdvSpriteDims()
	{
		return individualSpriteSize;
	}

	void Spritesheet::Update()
	{

	}

	BYTE* Spritesheet::GetImage()
	{
		return imageData;
	}

	bool Spritesheet::LoadSprite(std::string path)
	{
		if (!HAPI.LoadTexture(path, &imageData, spriteDims.width, spriteDims.height))
		{
			HAPI.UserMessage("Error! Unable to load sprite!" + path, "RoHAPI Engine");
			return false;
		}
		return true;
	}

	Vec2i Spritesheet::GetSpriteDims()
	{
		return spriteDims;
	}
}