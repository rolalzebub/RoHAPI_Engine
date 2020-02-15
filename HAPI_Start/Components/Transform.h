#pragma once
#include "util_includes.h"
#include "Component.h"

namespace RoHAPI {
	class GameObject;
	class Transform : public Component
	{
	private:
		Vec2d position = Vec2d(0);

	public:
		Transform(GameObject* parentObj_) : Component(parentObj_) { id = TransformC; position = Vec2d(0); };
		Transform(GameObject* parentObj_, SharedPtr<Transform> transform) : Component(parentObj_) {


			position = transform->GetPosition();
		}
		Transform() : Component() {};
		
		const Vec2d& GetPosition();

		void SetPosition(const Vec2d newPos) { position = newPos; };

		void Translate(Vec2d dir, double amount)
		{
			Vec2d magnitude = dir * (int)amount;
			SetPosition(position + magnitude);
		};

		void Translate(Vec2d translationAmount)
		{
			SetPosition(position + translationAmount);
		}
	};
}