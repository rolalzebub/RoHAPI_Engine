#pragma once
#include "util_includes.h"

namespace RoHAPI {

#define REngine Engine::Instance()

	class GameObject;

	class Engine
	{
	public:
		static Engine& Instance();

		void Start(const int& width = 1080, const int& height = 720);
		void Update();
		void Stop();

	private:
		static Engine* instance;
		double fixedUpdateTime = 1000.0/60.0;			//initializing tickrate at 60/second
		double deltaTime;
		double engineUpdateTime;
		std::vector<SharedPtr<GameObject>> m_gameObjects;
		bool showMask = false;
	};
}

