#pragma once
#include "Component.h"
namespace RoHAPI {

#define ColliderC 2
	class GameObject;

	

	class Collider :
		public Component
	{
	protected:
		Rect m_rect;
		bool collision = false;

	public:
		Collider(GameObject* parentObj_) : Component(parentObj_) { id = ColliderC; };
		Collider() : Component() { id = ColliderC; };
		~Collider() {};

		void Start() override {};
		void Start(Rect rect_) { m_rect = rect_; };
		void Update()override {};
		void Stop()override {};

		bool Collision() const { return collision; };
		void Collision(bool collision_) { collision = collision_; };


		virtual Rect GetColliderRect() const { return m_rect; };
		virtual void SetColliderRect(Rect newRect) { m_rect = newRect; }


	};

}