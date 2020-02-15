#pragma once
#include "Manager.h"
#include "Rigidbody.h"
namespace RoHAPI {
#define Physics PhysicsManager::Instance()
#define Gravity 9.8

	class Collider;
	class SpriteCollider;
	class Rigidbody;
	class PointGravity;

	class PhysicsManager : public Manager
	{
	private:
		static PhysicsManager* instance;
		std::vector<SharedPtr<Collider>> colliders;
		std::vector<SharedPtr<Rigidbody>> rigidbodies;

		std::vector<SharedPtr<SpriteCollider>> previousColliders;
		std::vector<SharedPtr<Rigidbody>> previousRigidbodies;
		std::vector<SharedPtr<PointGravity>> previousGravityAffectors;
	public:
		static PhysicsManager& Instance();
		~PhysicsManager() {};

		void Start() override;
		void Update() override;
		void Stop() override;
		void Reset();

		void AddCollider(SharedPtr<Collider> collider, int& colliderRef);
		void AddRigidbody(SharedPtr<Rigidbody> rigidbody);
		void AddGravityAffector(SharedPtr<PointGravity> grav_);
		std::vector<SharedPtr<Rigidbody>>& GetRigidbodies() { return rigidbodies; };
		Collider* GetCollider(int colliderID) const { return colliders[colliderID].get(); };

		bool CheckForCollision(Vec2d position, int colliderID,
			Vec2d otherPosition, int otherColliderID, Vec2d& collisionPoint);

		void ClearPhysicsManager();
		void ResetToPrevious();
		void ClearPrevious();

	protected:
		PhysicsManager() {};

	};
}
