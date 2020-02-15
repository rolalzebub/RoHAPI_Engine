#pragma once
#include "Level.h"

namespace RoHAPI {
	class PassCollider;
	class TestLevel :
		public Level
	{
	private:
		std::vector<SharedPtr<GameObject>> walls;
		std::vector<SharedPtr<PassCollider>> colliders;

		SharedPtr<GameObject> collectable;

		int wallStartSize;
		int wallShrinkDelta;
		double section_startTime;
		double wall_shift_delay;

		int offset_horizontal;
		int offset_vertical;
	public:
		void OnStart() override;
		void Update() override;

		void CreateLevel(Vec2d cameraPos);

		TestLevel(Level* toCopy_);
		TestLevel() = default;
		~TestLevel() = default;
	};

}

