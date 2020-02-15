#pragma once
#include "Transform.h"
#include "GameObject.h"
namespace RoHAPI {
	class Rigidbody :public Component
	{
	private:
		bool gravity = true;
		bool collided = false;
		double mass = 1.00;
		SharedPtr<Transform> transform;
		Vec2d velocity = Vec2d(0);
		Vec2d m_acceleration = Vec2d(0);
		Vec2d maxVelocity = Vec2d(10,10);
		double drag = 0;
	public:
		Rigidbody() {};
		Rigidbody(GameObject* parentObj_) : Component(parentObj_) { id = RigidbodyC; };
		~Rigidbody() {};

		void Start() override;
		void Update() override;
		void Stop()override {};

		bool useGravity() const { return gravity; };
		void useGravity(bool gravity_) { gravity = gravity_; };

		double getMass() const { return mass; };
		void setMass(double mass_) { mass = mass_; };
		void setAcceleration(Vec2d acceleration) { m_acceleration = acceleration; }

		Vec2d GetVelocity() const { return velocity; };
		void SetVelocity(Vec2d velocity_) { velocity = velocity_; };

		bool hasCollided() const { return collided; };
		void hasCollided(bool collided_) { collided = collided_; };

		void Rebound();

		void AddForce(Vec2d force_)
		{
			/*if (maxVelocity.x != 0.0 && maxVelocity.y != 0.0)
			{
				if (velocity.Length() + force_.Length() > maxVelocity.Length())
					force_ =  maxVelocity - velocity;
			}*/
			velocity += force_;
		};

		void ResetVelocity();

		double GetDrag() { return drag; }
		void SetDrag(double drag_) { drag = drag_; }
	};
}
