#pragma once
#include "Component.h"
namespace RoHAPI {
	class GameObject;

	class Sprite :public Component
	{

	private:
		BYTE* imageData = nullptr;
		Vec2i spriteDims;
		bool renderable = true;
		std::string name = "";

		bool flipX = false;

		

	public:

		Sprite(GameObject* parentObj) : Component(parentObj) { id = SpriteC; };
		Sprite(GameObject* parentObj, std::string path) : Component(parentObj) { id = SpriteC; m_parentObject = parentObj; LoadSprite(path); name = path; };
		Sprite(std::string path) { id = SpriteC; LoadSprite(path); };
		Sprite() :Component() { id = SpriteC; };
		~Sprite();

		bool isFlipped() { return flipX; }
		void isFlipped(bool flip) { flipX = flip; }

		bool LoadSprite(std::string path);

		void Update() override;

		void Stop() override;

		BYTE* GetImage();
		//Gets the Sprites dimentions in a Vec2 (width, height)
		Vec2i GetSpriteDims();

		bool CreateColouredBlock(Vec2i dimensions, HAPI_TColour colour);

		void Renderable(bool canBeRendered);
		bool Renderable() const;

		void ID(const int id_);
		int ID() const;

		void Name(const std::string& path);

	};
}