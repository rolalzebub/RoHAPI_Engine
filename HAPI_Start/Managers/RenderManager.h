#pragma once
#include "util_includes.h"
#include "Manager.h"
namespace RoHAPI {
#define Renderer RenderManager::Instance()
	
	class Sprite;
	class Spritesheet;
	class GameObject;
	class Animation;
	//A structure to hold the screens width, height and the pointer to the screens pixel data for the application
	struct Screen
	{
		Rect viewport;

		Vec2d world_pos = Vec2d(0, 0);

		//Size of the screen
		Vec2i screenDimensions;

		//Pointer to the screens pixel data
		BYTE* screenData;

		Screen(int width, int height, BYTE* screenPointer)
		{
			screenDimensions.width = width;
			screenDimensions.height = height;
			screenData = screenPointer;

			//viewport = Rect{ world_pos.y, world_pos.y + screenDimensions.height, world_pos.x, world_pos.x + screenDimensions.width };
			
		};
		Screen(int width, int height)
		{
			screenDimensions.width = width;
			screenDimensions.height = height;
			screenData = nullptr;

			//viewport = Rect{ world_pos.y, world_pos.y + screenDimensions.height, world_pos.x, world_pos.x + screenDimensions.width };
		};
		Screen()
		{
			screenDimensions.width = 500;
			screenDimensions.height = 500;
			screenData = nullptr;

			//viewport = Rect{ world_pos.y, world_pos.y + screenDimensions.height, world_pos.x, world_pos.x + screenDimensions.width };
		};

	};

	class RenderManager : public Manager
	{
	private:
		// The local instance of the render manager
		static RenderManager* instance;
		// Storage for local variables
		std::unique_ptr<Screen> screen;
		std::vector<SharedPtr<Sprite>> m_sprites;
		std::vector<SharedPtr<Animation>> animations;
		std::vector<SharedPtr<Sprite>> uiSprites;
		std::vector < SharedPtr<Spritesheet>> spritesheets;


		bool WithinScreenBounds(Vec2d position, Vec2i spriteDims);
	public:
		RenderManager() {};
		static RenderManager& Instance();
		~RenderManager() {};

		//Overide the base class' start stop and update functions
		void Start() override {};
		void Start(int Width = 0, int Height = 0, bool fullscreen = true);
		void Update() override;
		void Stop() override;

		// Clear the screen to a blanket colour by copying all of the pixels that were already set and then pasting them into the next set of the array. Fills the screen exponentially.
		void ClearScreen(const HAPI_TColour& backgroundColour);

		//Render an image on screen
		//int spriteIndex: The index of the sprite in the render managers vector of sprites
		//Vec3 renderPos: The position in 3D space the image should be rendered at
		void Render(const int& spriteIndex, const Vec2d& renderPos);

		//Render an image on screen
		//int spriteIndex: The index of the spritesheet in the render managers vector of spritesheet 
		//int idvSpriteIndex: The index of the sprite frame for the spritesheet 
		//Vec3 renderPos: The position in 3D space the image should be rendered at
		void RenderFromSpritesheet(const int& spriteIndex, const Vec2d& renderPos);


		//Returns a Vector2<int> of the screen dimentions
		const Vec2i GetScreenDimension();

		const Vec2d GetScreenPosition();
		void MoveScreen(Vec2d direction, int amount = 1);

		// Add a sprite to the render manager either by a pointer to a block of memory which contains the sprite
		// or from the manager laoding in a sprite from a specified path string

		SharedPtr<Sprite> AddSprite(const std::string& path, int& spriteIndexVar);
		bool AddSprite(SharedPtr<Sprite> spriteToAdd, int& spriteIndexVar);

		void AddSpritesheet(SharedPtr<Spritesheet> sheet, int& spritesheetIndex);

		// Add a spritesheet to the render manager either by a pointer to a block of memory which contains the spritesheet
		// or from the manager laoding in a spritesheet from a specified path string
		bool AddAnimation(SharedPtr<Animation> animation, int& animationIndex);

		SharedPtr<Sprite> GetSprite(const int& spriteIndex) const { return m_sprites[spriteIndex]; };
		// Returns a spritesheet from the vector or spritesheets that the render manager has

		void RenderText(Vec2d position, std::string textToRender, std::string font = "Arial");

	};

}
