#pragma once
#include "util_includes.h"
#include "GameObject.h"

namespace RoHAPI {
	class GameManager;

	class Level
	{
	protected:
		GameManager* game = nullptr;
		std::vector<SharedPtr<GameObject>> gameObjects;
		char* levelName = "";

	public:
		Level() {};
		Level(GameManager* game_, char* levelName_) :game(game_), levelName(levelName_) {};
		~Level() { gameObjects.clear(); };

		virtual void OnStart() {};
		virtual void Update() {};
		virtual void Stop() {};
	
		std::vector<SharedPtr<GameObject>> GetGameObjects() { return gameObjects; };
		void AddGameObject(SharedPtr<GameObject> newGameObject) { gameObjects.push_back(newGameObject); };
		char* GetLevelName() { return levelName; };
		void DeleteLevel() {
			for (auto g : gameObjects)
				g->Destroy();
			gameObjects.clear();
		}
	};
}