#include "TimeManager.h"

namespace RoHAPI {
	TimeManager* TimeManager::instance{ nullptr };

	TimeManager& TimeManager::Instance()
	{
		if (instance == nullptr)
			instance = new TimeManager;
		return *instance;
	}

	void TimeManager::Start()
	{
		lastTime = 0;
		time = HAPI.GetTime();
	}

	void TimeManager::Update()
	{
		lastTime = time;
		time = scale * HAPI.GetTime();
	}

	void TimeManager::Stop()
	{
		delete instance;
	}

	DWORD TimeManager::DeltaTime() const
	{
		return time - lastTime;
	}

	DWORD TimeManager::CurrentTime() const
	{
		return time;
	}
}