#include "RoHAPI.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "Transform.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameManager.h"
#include "AnimationManager.h"

namespace RoHAPI {
	Engine* Engine::instance{ nullptr };

	Engine& Engine::Instance()
	{
		if (instance == nullptr)
			instance = new Engine;
		return *instance;
	}

	void Engine::Start(const int& width, const int& height)
	{
		Time.Start();
		Renderer.Start(width, height, false); //3rd parameter is fullscreen or not
		//UI.Start();
		Physics.Start();
		Input.Start();
		Game.Start();
		Animator.Start();
		HAPI.SetShowFPS(true, 50, 50);
		engineUpdateTime = HAPI.GetTime();
	}

	void Engine::Update()
	{
		
		while (HAPI.Update()) 
		{

			Time.Update();

			m_gameObjects = Game.GetAllObjects();

			engineUpdateTime += HAPI.GetTime() - engineUpdateTime;

			Input.Update();

			Animator.Update();

			Renderer.Update();
			//how often to physics update?
			if(engineUpdateTime > fixedUpdateTime)
			{
				Physics.Update();
				Game.FixedUpdate();
				for (int i = 0; i < m_gameObjects.size(); i++)
				{
					auto gameObject = m_gameObjects[i];

					if (!gameObject->isActive()) continue;

					gameObject->FixedUpdate();
				}
				engineUpdateTime = 0;
			}

			Game.Update();

			for (auto gos : m_gameObjects)
			{
				if (!gos->isActive()) continue;

				if (gos->SpriteRef() > -1)
					Renderer.Render(gos->SpriteRef(), gos->GetTransform()->GetPosition());
				else if (gos->SpriteSheetRef() >= 0)
				{
					auto pos = gos->GetTransform()->GetPosition();
					Renderer.RenderFromSpritesheet(gos->SpriteSheetRef(), pos);
				}

				for (auto child : gos->GetChildren())
				{
					if (!child->isActive() || child->GetName() == "") continue;

					if (child->SpriteRef() > -1)
						Renderer.Render(child->SpriteRef(), child->GetTransform()->GetPosition());
					else if (child->SpriteSheetRef() >= 0)
					{
						auto pos = child->GetTransform()->GetPosition();
						Renderer.RenderFromSpritesheet(child->SpriteSheetRef(), pos);
					}
				}
				gos->Update();
			}

			if (Input.GetKeyUp(HK_ESCAPE))
			{
				HAPI.Close();
			}
		}
	}

	void Engine::Stop()
	{
		Animator.Stop();
		Game.Stop();
		Physics.Stop();
		Renderer.Stop();
		Input.Stop();
		Time.Stop();
		delete instance;
	}
}