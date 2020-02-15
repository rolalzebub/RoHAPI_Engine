#pragma once
#include "Manager.h"
#include "Animation.h"
namespace RoHAPI {
#define Animator AnimationManager::Instance()

	class AnimationManager :public Manager
	{

	private:
		// The local instance of the render manager
		static AnimationManager* instance;
		std::vector<SharedPtr<Animation>> animations;

		public:
			static AnimationManager& Instance();
			~AnimationManager() {};

			//Overide the base class' start stop and update functions
			void Start() override;
			void Update() override;
			void Stop() override;

			void AddAnimation(SharedPtr<Animation> animation) { animations.push_back(animation); };

		protected:
			AnimationManager() {};

	};
}
