#include "AnimationManager.h"
namespace RoHAPI {
	AnimationManager* AnimationManager::instance{ nullptr };

	// Creates / get a singleton instance of the rendering manager
	AnimationManager& AnimationManager::Instance()
	{
		if (instance == nullptr)
			instance = new AnimationManager;
		return *instance;
	}

	void AnimationManager::Start()
	{
		for (const auto a : animations)
		{
			a->Start();
		}
	}

	void AnimationManager::Update()
	{
		for (const auto a : animations)
		{
			a->Update();
		}
	}

	void AnimationManager::Stop()
	{
		delete instance;
	}

}