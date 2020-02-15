#pragma once
#include "Manager.h"
#include "GameObject.h"
#include "TestLevel.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TestPlayer.h"

namespace RoHAPI {
#define Game GameManager::Instance()

	enum Difficulty
	{
		Easy = 1,
		Normal = 2,
		Hard = 4,
		Insane = 8
	};

	class GameManager : public Manager
	{
	private:

		SharedPtr<TestPlayer> test;
		TestLevel level;
		static GameManager* instance;

		int currentScore = 0;
		Difficulty difficulty = Difficulty::Normal;

		bool gameShouldEnd = false;

	public:
		static GameManager& Instance();

		void Start() override;
		void FixedUpdate() override;
		void Update() override;
		void Stop() override;

		void DeleteLevels();

		SharedPtr<Level> CurrentLevel();
		void ReloadGame();
		
		std::vector<SharedPtr<GameObject>> GetAllObjects();

		void Destroy(SharedPtr<GameObject> gameobject);
		void AddLevel(SharedPtr<Level> newLevel);

		void IncreaseScore(int scoreToAdd = 1) { currentScore += (scoreToAdd * difficulty); };

		int GetScore() const { return currentScore; };

		void SetDifficulty(const Difficulty newDifficulty) { difficulty = newDifficulty; };
		Difficulty GetDifficulty() const { return difficulty; };

		void GameOver(bool hasWon, int score);

		bool IsGameOver() const { return gameShouldEnd; };
		void SetGameOver(const bool overState) { gameShouldEnd = overState; };

		void Reset();


	};

}