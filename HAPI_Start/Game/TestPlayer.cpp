#include "TestPlayer.h"
#include "InputManager.h"
#include "Transform.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
namespace RoHAPI {
	TestPlayer::TestPlayer()
	{

		m_name = "Test_Player_Object";
		active = true;
		testPlayerSprite = MakeSharedPtr<Spritesheet>(this);
		testPlayerSprite->LoadSprite(sprite_pathname);
		testPlayerSprite->SetIdvSpriteSize(Vec2i(46, 50));

		animation = MakeSharedPtr<Animation>(this);
		animation->SetSpritesheet(testPlayerSprite.get());

		Renderer.AddSpritesheet(testPlayerSprite, m_spritesheetIndex);
		Renderer.AddAnimation(animation, m_spritesheetIndex);

		animation->AddAnimationClip(idle);
		animation->AddAnimationClip(walk);


		collider = MakeSharedPtr<Collider>(this);
		collider->SetColliderRect(testPlayerSprite->GetIdvSpriteDims());
		Physics.AddCollider(collider, m_colliderIndex);

		AddComponent(collider);
		AddComponent(testPlayerSprite);
		AddComponent(animation);
	}

	void TestPlayer::Start() {
		animation->SetAnimation("walk");
	}

	void TestPlayer::Update()
	{
		
		moveDirection = Vec2d(0);
		if (Input.GetKey(HK_LEFT))
			moveDirection.x -= 1;

		if (Input.GetKey(HK_RIGHT))
			moveDirection.x += 1;

		if (Input.GetKey(HK_UP))
			moveDirection.y -= 1;

		if (Input.GetKey(HK_DOWN))
			moveDirection.y += 1;
		


		screenDeltaMove = Vec2d(0);
		if (Input.GetKey('S'))
			screenDeltaMove.y += 1;
		if (Input.GetKey('W'))
			screenDeltaMove.y -= 1;
		if (Input.GetKey('A'))
			screenDeltaMove.x -= 1;
		if (Input.GetKey('D'))
			screenDeltaMove.x += 1;

		
	}

	void TestPlayer::FixedUpdate() {
		m_transform->Translate(moveDirection);
		Renderer.MoveScreen(screenDeltaMove);

		if (moveDirection.Length() == 0 &&
			animation->GetCurrentAnimationName() != "idle")
			animation->SetAnimation("idle");

		if (moveDirection.Length() != 0 &&
			animation->GetCurrentAnimationName() != "walk")
			animation->SetAnimation("walk");


		if (moveDirection.x < 0)
			animation->isFlipped(true);

		if (moveDirection.x > 0) {
			animation->isFlipped(false);
		}
	}

	void TestPlayer::OnCollisionEnter(CollisionInfo collidedObject)
	{
		std::cout << "starting collision with " + collidedObject.collided_object->GetName() << std::endl;
	}

	void TestPlayer::OnCollisionStay(CollisionInfo collidedObject)
	{
		std::cout << "still colliding with " + collidedObject.collided_object->GetName() << std::endl;
	}

	void TestPlayer::OnCollisionExit(CollisionInfo collidedObject)
	{
		std::cout << "stopped colliding with " + collidedObject.collided_object->GetName() << std::endl;
	}

	void TestPlayer::Stop() {
	}
}