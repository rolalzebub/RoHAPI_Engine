#pragma once
#include "GameObject.h"
#include "Spritesheet.h"
#include "PhysicsManager.h"
#include "SpriteCollider.h"
#include "AnimationManager.h"
#include "SlingshotController.h"
namespace RoHAPI {
	class TestPlayer :
		public GameObject
	{
	private:
		std::string sprite_pathname = "Data/player-spritemap-v9.png";
		
		Vec2d moveDirection;
		Vec2d screenDeltaMove = Vec2d(0);

		SharedPtr<Spritesheet> testPlayerSprite;
		SharedPtr<Animation> animation;
		SharedPtr<Rigidbody> rigidbody;
		SharedPtr<Collider> collider;

		AnimationClip idle = AnimationClip("idle", Vec2i(0, 0), Vec2i(46, 50));
		AnimationClip walk = AnimationClip("walk", Vec2i(0, 150), Vec2i(360, 200));
	public:
		TestPlayer();
		void Start() override;
		void Update() override;
		void Stop() override;
		void FixedUpdate() override;

		void OnCollisionEnter(CollisionInfo collidedObject) override;
		void OnCollisionStay(CollisionInfo collidedObject) override;
		void OnCollisionExit(CollisionInfo collidedObject) override;
	};
}