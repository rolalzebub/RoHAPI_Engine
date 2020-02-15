#include "GameManager.h"
#include "AnimationManager.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include "Level.h"

namespace RoHAPI {

	GameManager* GameManager::instance{ nullptr };

	GameManager& GameManager::Instance()
	{
		if (instance == nullptr)
			instance = new GameManager;
		return *instance;
	}

	void GameManager::Start()
	{
		level.OnStart();
		for (auto gos : level.GetGameObjects())
			gos->Start();
		test = MakeSharedPtr<TestPlayer>();
		test->Start();
	}

	void GameManager::AddLevel(SharedPtr<Level> newLevel)
	{
	}

	void GameManager::Destroy(SharedPtr<GameObject> gameobject)
	{
		gameobject->isActive(false);
	}

	void GameManager::FixedUpdate()
	{
		for (auto gos : level.GetGameObjects()) {
			if (gos->isActive())
				gos->FixedUpdate();
		}
	}

	void GameManager::Update()
	{
		level.Update();
		test->Update();
		if (Input.GetKeyUp(HK_F5))
		{
			ReloadGame();
		}

		if (Input.GetKeyUp(HK_F6))
		{
			difficulty = Difficulty::Easy;
			ReloadGame();
		}
		if (Input.GetKeyUp(HK_F7))
		{
			difficulty = Difficulty::Normal;
			ReloadGame();
		}
		if (Input.GetKeyUp(HK_F8))
		{
			difficulty = Difficulty::Hard;
			ReloadGame();
		}
		if (Input.GetKeyUp(HK_F9))
		{
			difficulty = Difficulty::Insane;
			ReloadGame();
		}
	}

	void GameManager::Stop()
	{
		test->Stop();
		DeleteLevels();
		delete instance;
	}

	void GameManager::DeleteLevels()
	{
		
	}

	SharedPtr<Level> GameManager::CurrentLevel()
	{
		return MakeSharedPtr<TestLevel>(level);
	}

	void GameManager::ReloadGame()
	{
		
	}

	std::vector<SharedPtr<GameObject>> GameManager::GetAllObjects()
	{
		auto& new_vec = CurrentLevel()->GetGameObjects();
		new_vec.push_back(test);
		return new_vec;
	}


	void GameManager::GameOver(bool hasWon, int score)
	{
		gameShouldEnd = true;
	}

	void GameManager::Reset()
	{
		currentScore = 0;
	}

}