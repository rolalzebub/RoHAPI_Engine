#pragma once
#include "Component.h"
#include "RenderManager.h"
namespace RoHAPI {
	class Spritesheet :public Component
	{
	private:
		int id = 0;
		BYTE* imageData = nullptr;
		Vec2i spriteDims;
		Vec2i individualSpriteSize = Vec2i(0);
		std::string name;

	public:
		Spritesheet(GameObject* parentObj) :Component(parentObj) { };
		Spritesheet(GameObject* parentObj, const std::string& path) :Component(parentObj) { LoadSprite(path); name = path; };
		Spritesheet(GameObject* parentObj, const std::string& path, Vec2i idvSpriteSize) : Component(parentObj) {
			LoadSprite(path);
			individualSpriteSize = idvSpriteSize;
			name = path;
		};
		Spritesheet(const std::string& path, Vec2i idvSpriteSize) : Component() {
			LoadSprite(path);
			individualSpriteSize = idvSpriteSize;
			name = path;
		};
		Spritesheet() : Component() {  };
		~Spritesheet();

		BYTE* GetImage();
		bool LoadSprite(std::string path);
		//Gets the Sprites dimentions in a Vec2 (width, height)
		Vec2i GetSpriteDims();

		const Vec2i GetIdvSpriteDims();
		void SetIdvSpriteSize(const Vec2i size) { individualSpriteSize = size; };

		void Name(const std::string& path)
		{
			name = path;
		};

		void Update() override;

	};
}
