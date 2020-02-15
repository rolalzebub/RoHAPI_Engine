#pragma once
#include "util_includes.h"
namespace RoHAPI {

	class Engine
	{
	public:
		static Engine& Instance();

		void Start(const int& width = 1080, const int& height = 720);
		void Update();
		void Stop();

	private:
		Engine() {};

	private:
		static Engine* instance;
		DWORD fixedUpdateTime;
		DWORD engineUpdateTime;
		std::vector<SharedPtr<GameObject>> m_gameObjects;
		bool showMask = false;
	};


#define REngine Engine::Instance()
}
