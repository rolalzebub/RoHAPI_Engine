#include "RenderManager.h"
#include "Sprite.h"
#include "Spritesheet.h"
#include "GameObject.h"
#include"Animation.h"
namespace RoHAPI {
	RenderManager* RenderManager::instance{ nullptr };

	bool RenderManager::WithinScreenBounds(Vec2d position, Vec2i spriteDims)
	{

		if (position.x + spriteDims.width < screen->world_pos.x - (screen->screenDimensions.width / 2) ||
			position.y + spriteDims.height < screen->world_pos.y - (screen->screenDimensions.height / 2) ||
			position.x > screen->world_pos.x + (screen->screenDimensions.width / 2) ||
			position.y > screen->world_pos.y + (screen->screenDimensions.height / 2))
			return false;

		return true;
	}

	// Creates / get a singleton instance of the rendering manager
	RenderManager& RenderManager::Instance()
	{
		if (instance == nullptr)
			instance = new RenderManager;
		return *instance;
	}

	//Starts the rendering manager with the supplied screens dimentions and whether its fullscreen or not
	void RenderManager::Start(int Width, int Height, bool fullscreen)
	{
		int screenWidth = Width, screenHeight = Height;

		//Start the HAPI API to create the window
		if (!HAPI.Initialise(screenWidth, screenHeight))
		{
			return;
		}
		//Create new unique screen data pointer
		screen = std::make_unique<Screen>(screenWidth, screenHeight, HAPI.GetScreenPointer());

	}

	void RenderManager::Update()
	{
		ClearScreen(HAPI_TColour::BLACK);

		for (auto s : m_sprites)
			s->Update();

		for (auto s : animations)
			s->Update();
	}

	void RenderManager::ClearScreen(const HAPI_TColour& backgroundColour)
	{
		Vec2i screenDims = GetScreenDimension();
		BYTE* tempPtr = screen->screenData;
		for (int i = 0; i < screenDims.width * screenDims.height; i++) {
			memcpy(tempPtr, &HAPI_TColour::BLACK, sizeof(HAPI_TColour));
			tempPtr += 4;
		}
	};


	//Render an image on screen
	//int spriteIndex: The index of the sprite in the render managers vector of sprites
	//Vec2 renderPos: The position in 2D space the image should be rendered at
	void RenderManager::Render(const int& spriteIndex, const Vec2d& renderPos)
	{

		Vec2d screenPos = screen->world_pos;
		Vec2i screenDims = screen->screenDimensions;
		Vec2i spriteDims = m_sprites[spriteIndex]->GetSpriteDims();

		Vec2d finalRenderPos = renderPos;
		finalRenderPos.x -= spriteDims.width / 2;
		finalRenderPos.y -= spriteDims.height / 2;

		screenPos.x -= screenDims.width / 2;
		screenPos.y -= screenDims.height / 2;


		//If the image is off of the screen dont execute the render function
		if (!WithinScreenBounds(finalRenderPos, spriteDims))
			return;
		//A local "rectangle" which handles image clipping
		double startX = 0;
		double startY = 0;
		double endX = 0;
		double endY = 0;

		//If the image is off of the left side of the screen offset the left side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.x < screenPos.x)
			startX = abs(finalRenderPos.x - screenPos.x);
		//If the image is off of the top side of the screen offset the top side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.y < screenPos.y)
			startY = abs(finalRenderPos.y - screenPos.y);
		//If the image is off of the right side of the screen offset the right side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.x + spriteDims.width > screenPos.x + (screenDims.width))
			endX = (spriteDims.width + finalRenderPos.x) - (screenPos.x + (screenDims.width));
		//If the image is off of the bottom side of the screen offset the bottom side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.y + spriteDims.height > screenPos.y + (screenDims.height))
			endY = (finalRenderPos.y + spriteDims.height) - (screenPos.y + (screenDims.height));

		Rect sourceRect{ startY, spriteDims.height - endY, startX, spriteDims.width - endX };


		BYTE* imgPtr = m_sprites[spriteIndex]->GetImage();
		BYTE* screenPtr = screen->screenData;

		int offset = ((finalRenderPos.y - screenPos.y) * screenDims.width + (finalRenderPos.x - screenPos.x)) * 4;

		//The rendering loop for each pixel of the images clipped rectangle

		if (!m_sprites[spriteIndex]->isFlipped()) {
			for (int i = sourceRect.GetRectDims().top; i < sourceRect.GetRectDims().bottom; i++) {
				for (int j = sourceRect.GetRectDims().left; j < sourceRect.GetRectDims().right; j++) {
					HAPI_TColour* sourceColour = (HAPI_TColour*)(imgPtr + ((i * spriteDims.width) + j) * 4);
					HAPI_TColour* destColour = (HAPI_TColour*)(screen->screenData + offset + ((i * screenDims.width + j) * 4));


					if (sourceColour != &HAPI_TColour::ZERO) {
						if ((BYTE*)destColour < (BYTE*)(screen->screenData + ((screenDims.width * screenDims.height) * 4)) &&
							(BYTE*)destColour >= (BYTE*)(screen->screenData)) {

							if (sourceColour->alpha > 0) {
								if (sourceColour->alpha < 255) {
									float alpha = sourceColour->alpha / 255.0f;

									destColour->red = (sourceColour->red * alpha) + ((1.0 - alpha) * destColour->red);
									destColour->green = (sourceColour->green * alpha) + ((1.0 - alpha) * destColour->green);
									destColour->blue = (sourceColour->blue * alpha) + ((1.0 - alpha) * destColour->blue);
								}

								else
									memcpy(destColour, sourceColour, sizeof(HAPI_TColour));
							}
						}
					}
				}
			}
		}

		else {
			int screen_Y = sourceRect.GetRectDims().top;
			for (int i = sourceRect.GetRectDims().top; i < sourceRect.GetRectDims().bottom; i++) {
				int screen_X = sourceRect.GetRectDims().right;
				for (int j = sourceRect.GetRectDims().right; j >= sourceRect.GetRectDims().left; j--) {
					HAPI_TColour* sourceColour = (HAPI_TColour*)(imgPtr + ((i * spriteDims.width) + j) * 4);
					HAPI_TColour* destColour = (HAPI_TColour*)(screen->screenData + offset + ((screen_Y * screenDims.width + screen_X) * 4));


					if (sourceColour != &HAPI_TColour::ZERO) {
						if ((BYTE*)destColour < (BYTE*)(screen->screenData + ((screenDims.width * screenDims.height) * 4)) &&
							(BYTE*)destColour >= (BYTE*)(screen->screenData)) {

							if (sourceColour->alpha > 0) {
								if (sourceColour->alpha < 255) {
									float alpha = sourceColour->alpha / 255.0f;

									destColour->red = (sourceColour->red * alpha) + ((1.0 - alpha) * destColour->red);
									destColour->green = (sourceColour->green * alpha) + ((1.0 - alpha) * destColour->green);
									destColour->blue = (sourceColour->blue * alpha) + ((1.0 - alpha) * destColour->blue);
								}

								else
									memcpy(destColour, sourceColour, sizeof(HAPI_TColour));
							}
						}
					}
					screen_X++;
				}
				screen_Y++;
			}
		}
	};

	//int spriteIndex: The index of the spritesheet in the render managers vector of spritesheet 
	//int idvSpriteIndex: The index of the sprite frame for the spritesheet 
	//Vec2 renderPos: The position in 2D world space the image should be rendered at
	void RenderManager::RenderFromSpritesheet(const int& spriteIndex, const Vec2d& renderPos)
	{

		//The current animation from the index
		Animation* anim = animations[spriteIndex].get();
		Vec2i spriteIdvDims = anim->GetIdvSpriteDims();

		Vec2d screenPos = screen->world_pos;
		Vec2i screenDims = screen->screenDimensions;
		Vec2i spriteDims = anim->GetSpritesheetDims();

		Vec2d finalRenderPos = renderPos;

		finalRenderPos.x -= spriteIdvDims.width / 2;
		finalRenderPos.y -= spriteIdvDims.height / 2;

		screenPos.x -= screenDims.width / 2;
		screenPos.y -= screenDims.height / 2;

		//if the rendered position is off of the screen dont render
		if (!WithinScreenBounds(finalRenderPos, spriteIdvDims))
			return;

		//A local "rectangle" which handles image clipping
		int startX = 0;
		int startY = 0;
		int endX = 0;
		int endY = 0;

		//If the image is off of the left side of the screen offset the left side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.x < screenPos.x)
			startX = abs(finalRenderPos.x - screenPos.x);
		//If the image is off of the top side of the screen offset the top side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.y < screenPos.y)
			startY = abs(finalRenderPos.y - screenPos.y);
		//If the image is off of the right side of the screen offset the right side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.x + spriteIdvDims.width > screenPos.x + screenDims.width)
			endX = (spriteIdvDims.width + finalRenderPos.x) - (screenPos.x + screenDims.width);
		//If the image is off of the bottom side of the screen offset the bottom side of the rectangle with the amount its off of the screen by
		if (finalRenderPos.y + spriteIdvDims.height > screenPos.y + screenDims.height)
			endY = (finalRenderPos.y + spriteIdvDims.height) - (screenPos.y + screenDims.height);

		BYTE* imgPtr = anim->GetCurrentSprite();
		BYTE* screenPtr = screen->screenData;

		int yLoopEnd = spriteIdvDims.height - endY;
		int xLoopEnd = spriteIdvDims.width - endX;

		int offset = ((finalRenderPos.y - screenPos.y) * screenDims.width + (finalRenderPos.x - screenPos.x)) * 4;


		if (anim->isFlipped() == false) {
			//The rendering loop for each pixal of the images clipped rectangle
			for (int i = startY; i < yLoopEnd; i++)
			{
				for (int j = startX; j < xLoopEnd; j++)
				{
					HAPI_TColour* sourceColour = (HAPI_TColour*)((imgPtr)+((i * spriteDims.width) + j) * 4);
					HAPI_TColour* destColour = (HAPI_TColour*)((screen->screenData + offset) + ((i * screenDims.width + j) * 4));


					if (sourceColour != &HAPI_TColour::ZERO) {
						if ((BYTE*)destColour < (BYTE*)(screen->screenData + ((screenDims.width * screenDims.height) * 4)) &&
							(BYTE*)destColour >= (BYTE*)(screen->screenData)) {

							if (sourceColour->alpha > 0) {
								if (sourceColour->alpha < 255) {
									float alpha = sourceColour->alpha / 255.0f;

									destColour->red = (sourceColour->red * alpha) + ((1.0 - alpha) * destColour->red);
									destColour->green = (sourceColour->green * alpha) + ((1.0 - alpha) * destColour->green);
									destColour->blue = (sourceColour->blue * alpha) + ((1.0 - alpha) * destColour->blue);
								}

								else
									memcpy(destColour, sourceColour, sizeof(HAPI_TColour));
							}
						}
					}
				}
			}
		}
		else {
			int screen_Y = startY;
			for (int i = startY; i < yLoopEnd; i++)
			{
				int screen_X = startX;
				for (int j = xLoopEnd - 1; j >= startX; j--)
				{
					HAPI_TColour* sourceColour = (HAPI_TColour*)((imgPtr)+((i * spriteDims.width) + j) * 4);
					HAPI_TColour* destColour = (HAPI_TColour*)((screen->screenData + offset) + ((screen_Y * screenDims.width + screen_X) * 4));


					if (sourceColour != &HAPI_TColour::ZERO) {
						if ((BYTE*)destColour < (BYTE*)(screen->screenData + ((screenDims.width * screenDims.height) * 4)) &&
							(BYTE*)destColour >= (BYTE*)(screen->screenData)) {

							if (sourceColour->alpha > 0) {
								if (sourceColour->alpha < 255) {
									float alpha = sourceColour->alpha / 255.0f;

									destColour->red = (sourceColour->red * alpha) + ((1.0 - alpha) * destColour->red);
									destColour->green = (sourceColour->green * alpha) + ((1.0 - alpha) * destColour->green);
									destColour->blue = (sourceColour->blue * alpha) + ((1.0 - alpha) * destColour->blue);
								}

								else
									memcpy(destColour, sourceColour, sizeof(HAPI_TColour));
							}
						}
					}
					screen_X++;
				}
				screen_Y++;
			}
		}
	}


	//Returns a Vector2<int> of the screen dimentions
	const Vec2i RenderManager::GetScreenDimension()
	{
		return screen->screenDimensions;
	}

	const Vec2d RenderManager::GetScreenPosition()
	{
		Vec2d screenPos = screen->world_pos;
		/*screenPos.x -= screen->screenDimensions.width/2;
		screenPos.y -= screen->screenDimensions.height/2;*/

		return screenPos;
	}

	void RenderManager::MoveScreen(Vec2d direction, int amount)
	{
		screen->world_pos += direction * amount;
	}

	// Add a sprite to the render manager by loading in a sprite from a specified path string
	SharedPtr<Sprite> RenderManager::AddSprite(const std::string& path, int& spriteIndexVar)
	{
		m_sprites.push_back(MakeSharedPtr<Sprite>(path));
		spriteIndexVar = m_sprites.size() - 1;

		if (spriteIndexVar > -1)
			return m_sprites[spriteIndexVar];
		else return nullptr;
	}

	// Add a sprite to the render manager by a pointer to a block of memory which contains the sprite
	bool RenderManager::AddSprite(SharedPtr<Sprite> spriteToAdd, int& spriteIndexVar)
	{
		m_sprites.push_back(spriteToAdd);
		spriteIndexVar = m_sprites.size() - 1;
		return true;
	}

	void RenderManager::AddSpritesheet(SharedPtr<Spritesheet> sheet, int& spritesheetIndex)
	{
		spritesheets.push_back(sheet);
		spritesheetIndex = spritesheets.size() - 1;
	}

	// Add a spritesheet to the render manager by loading in a sprite from a specified path string
	bool RenderManager::AddAnimation(SharedPtr<Animation> animation, int& spriteSheetIndex)
	{
		animations.push_back(animation);
		spriteSheetIndex = animations.size() - 1;
		return true;
	}

	void RenderManager::Stop()
	{

		//Deletes the sprites from the vector and then clears it
		m_sprites.clear();

		for (auto s : animations)
			s->Stop();

		//Deletes the spritesheets from the vector and then clears it
		animations.clear();

		//Delete the instance of the rendering manager
		delete instance;
	}



	void RenderManager::RenderText(Vec2d position, std::string textToRender, std::string font)
	{
		if (HAPI.ChangeFont(font))
			HAPI.RenderText((int)position.x, (int)position.y, HAPI_TColour::RED, textToRender);
		else std::cout << "Failed to load font" << std::endl;
	}

}