#include "InputManager.h"
namespace RoHAPI {
	InputManager* InputManager::instance{ nullptr };

	InputManager::~InputManager()
	{

	};
	InputManager& InputManager::Instance()
	{
		if (instance == nullptr)
			instance = new InputManager;
		return *instance;
	}

	bool InputManager::ControllerIDExists(int id)
	{
		if (activeControllersThisFrame[id])
			return true;
		else
			return false;
	}

	bool InputManager::ControllerConnected(int id)
	{
		return HAPI.GetControllerData(id).isAttached;
	}


	void InputManager::Reset()
	{
		/*for (int i = 0; i < maxControllers; ++i)
		{
			activeControllersThisFrame[i] = false;
			activeControllersLastFrame[i] = false;
		}*/
	}

	void InputManager::Start()
	{
		time = HAPI.GetTime();

		for (int i = 0; i < maxControllers; i++) {
			controllers.push_back(HAPI.GetControllerData(i));
			activeControllersThisFrame.push_back(false);
		}
	}

	void InputManager::Update()
	{

		Input.keyboardBuffer = Input.keyboard;
		Input.controllersBuffer = Input.controllers;

		Input.keyboard = HAPI.GetKeyboardData();
		Input.mouse = HAPI.GetMouseData();


		for (int i = 0; i < maxControllers; i++)
		{
			if (HAPI.GetControllerData(i).isAttached)
			{
				Input.activeControllersThisFrame[i] = true;
				Input.controllers[i] = HAPI.GetControllerData(i);
			}
			else
			{
				Input.activeControllersThisFrame[i] = false;
			}
		}
	}

	void InputManager::Stop()
	{
		delete instance;
	}
}