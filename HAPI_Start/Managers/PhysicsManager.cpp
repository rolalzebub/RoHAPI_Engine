#include "PhysicsManager.h"
#include "SpriteCollider.h"
#include "Sprite.h"
#include "Transform.h"
#include "GameManager.h"
namespace RoHAPI {
#define Physics PhysicsManager::Instance()
	PhysicsManager* PhysicsManager::instance{ nullptr };

	PhysicsManager& PhysicsManager::Instance()
	{
		if (instance == nullptr)
			instance = new PhysicsManager;
		return *instance;
	}

	void PhysicsManager::Start()
	{

	}

	void PhysicsManager::Update()
	{
		for (int i = 0; i < colliders.size(); i++) {
			auto& r = colliders[i];
			for (int j = i + 1; j < colliders.size(); j++) {
				auto& s = colliders[j];
				
				//TODO: Calculate point of collision if result is true
				Vec2d collision_point = Vec2d(0);
				bool collision_result = CheckForCollision(r->GetParent()->GetTransform()->GetPosition(), r->GetParent()->ColliderRef(), s->GetParent()->GetTransform()->GetPosition(), s->GetParent()->ColliderRef(), collision_point);	
				
				switch (collision_result)
				{

				case true:
					if (r->Collision() == false) {
						r->Collision(true);
						r->GetParent()->OnCollisionEnter((CollisionInfo{ s->GetParent(), collision_point }));
						
					}
					else
					{
						r->GetParent()->OnCollisionStay(CollisionInfo{s->GetParent(), collision_point});
					}

					if (s->Collision() == false) {
						s->Collision(true);
						s->GetParent()->OnCollisionEnter(CollisionInfo{ r->GetParent(), collision_point });
					}
					else
					{
						s->GetParent()->OnCollisionStay(CollisionInfo{r->GetParent(), collision_point});
					}
					break;

				case false:
					if (r->Collision() == true &&
						s->Collision() == true) {

						r->Collision(false);
						s->Collision(false);

						r->GetParent()->OnCollisionExit((CollisionInfo{ s->GetParent(), collision_point }));
						s->GetParent()->OnCollisionExit((CollisionInfo{ r->GetParent(), collision_point }));
					}
					break;
				}
			}
		}
	}

	void PhysicsManager::Stop()
	{
		for (auto c : colliders)
			c = nullptr;
		for (auto r : rigidbodies)
			r = nullptr;

		colliders.clear();
		rigidbodies.clear();
		//Delete the instance of the rendering manager
		delete instance;
	}

	void PhysicsManager::AddCollider(SharedPtr<Collider> collider, int& colliderRef)
	{
		colliders.push_back(collider);
		colliderRef = colliders.size() - 1;
	}

	void PhysicsManager::AddRigidbody(SharedPtr<Rigidbody> rigidbody)
	{
		rigidbodies.push_back(rigidbody);
	}

	void PhysicsManager::AddGravityAffector(SharedPtr<PointGravity> grav_)
	{
	}

	void PhysicsManager::Reset()
	{
		for (auto c : colliders)
			c = nullptr;
		for (auto r : rigidbodies)
			r = nullptr;

		colliders.clear();
		rigidbodies.clear();
	}

	bool PhysicsManager::CheckForCollision(Vec2d position, int colliderID,
		Vec2d otherPosition, int otherColliderID, Vec2d& collisionPoint)
	{

		SharedPtr<Collider> collider = colliders[colliderID];
		SharedPtr<Collider> otherCollider = colliders[otherColliderID];

		Rect playerCollisionRect = collider->GetColliderRect();
		Rect enemyCollisionRect = otherCollider->GetColliderRect();

		Vec2d finalPos = position;
		finalPos.x -= playerCollisionRect.Width()/2;
		finalPos.y -= playerCollisionRect.Height()/2;

		Vec2d otherFinalPos = otherPosition;
		otherFinalPos.x -= enemyCollisionRect.Width()/2;
		otherFinalPos.y -= enemyCollisionRect.Height()/2;

		playerCollisionRect.Translate(finalPos.x, finalPos.y);
		enemyCollisionRect.Translate(otherFinalPos.x, otherFinalPos.y);


		if (!playerCollisionRect.Intersects(enemyCollisionRect))
			return false;

		return true;

	}


	//Clear the buffers that store sprites in the renderer
	void PhysicsManager::ClearPhysicsManager()
	{
		
	}

	//Reset the live sprite buffers to what they were before a reload occured
	void PhysicsManager::ResetToPrevious()
	{
	}

	//Clear the previous buffer of sprites - successful reload of levels
	void PhysicsManager::ClearPrevious()
	{
		previousColliders.clear();
		previousGravityAffectors.clear();
		previousRigidbodies.clear();
	}
}