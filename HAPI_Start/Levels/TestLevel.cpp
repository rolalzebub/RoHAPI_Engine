#include "TestLevel.h"
#include "GameManager.h"
#include "Sprite.h"
#include "RenderManager.h"
#include "GameManager.h"
namespace RoHAPI {

	TestLevel::TestLevel(Level* toCopy_)
	{
		gameObjects = toCopy_->GetGameObjects();
	}
	void TestLevel::OnStart()
	{
		Vec2i screenDims = Renderer.GetScreenDimension();

		offset_vertical = (50 / 100.0) * (screenDims.height);
		offset_horizontal = (50 / 100.0) * (screenDims.width);


		CreateLevel(Renderer.GetScreenPosition());
		//create coins
		Game.AddLevel(MakeSharedPtr<TestLevel>(this));
		
		//create walls


	}

	void TestLevel::Update()
	{
		for (auto gos : gameObjects)
			gos->Update();
		
	}
	void TestLevel::CreateLevel(Vec2d cameraPos)
	{

		/*collectable = MakeSharedPtr<GameObject>();
		auto sprite = MakeSharedPtr<Spritesheet>(collectable.get());
		sprite->LoadSprite("Data/Coins-PNG.png");
		sprite->SetIdvSpriteSize(Vec2i(284 / 8, 194 / 3));

		auto anim = MakeSharedPtr<Animation>(collectable.get());
		anim->SetSpritesheet(sprite.get());
		anim->AddAnimationClip(AnimationClip("coin_rotate", Vec2i(0, 0), Vec2i(284, 194/3)));
		anim->SetAnimation("coin_rotate");
		collectable->AddComponent(sprite);
		collectable->AddComponent(anim);

		int spritesheetRef, animRef;
		Renderer.AddSpritesheet(sprite, spritesheetRef);
		Renderer.AddAnimation(anim, animRef);
		collectable->SpriteSheetRef(animRef);
		

		collectable->GetTransform()->SetPosition(Vec2d(-50, 0));

		AddGameObject(collectable);*/
		//Create walls
		for (int i = 0; i < 4; i++) {

			SharedPtr<PassCollider> new_collider = MakeSharedPtr<PassCollider>();
			colliders.push_back(new_collider);
			

			SharedPtr<GameObject> new_wall = MakeSharedPtr<GameObject>();
			walls.push_back(new_wall);

			

			SharedPtr<Sprite> ceiling_sprite = MakeSharedPtr<Sprite>(walls[i].get());
			
			if (i % 2 == 0) {												//checking which part of the loop we're in to see which wall to make
				ceiling_sprite->CreateColouredBlock(Vec2i(800, 20), HAPI_TColour::RED);
				if (i == 0) {
					walls[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x, cameraPos.y - offset_vertical));
					colliders[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x - offset_horizontal, cameraPos.y - offset_vertical));
				}
				else {
					walls[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x, cameraPos.y + offset_vertical));
					colliders[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x - offset_horizontal, cameraPos.y + offset_vertical));
				}
			}
			else {

				ceiling_sprite->CreateColouredBlock(Vec2i(20, 400), HAPI_TColour::RED);
				if (i == 3) {
					colliders[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x + offset_horizontal, cameraPos.y - offset_vertical));
					walls[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x - offset_horizontal, cameraPos.y));
				}
				else
				{
					walls[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x + offset_horizontal, cameraPos.y));
					colliders[i]->GetTransform()->SetPosition(Vec2d(cameraPos.x + offset_horizontal, cameraPos.y + offset_vertical));
				}
			}
			int sprite_ref = -1;

			SharedPtr<Collider> wall_collider = MakeSharedPtr<SpriteCollider>(walls[i].get());
			wall_collider->SetColliderRect(ceiling_sprite->GetSpriteDims());
			Renderer.AddSprite(ceiling_sprite, sprite_ref);
			walls[i]->AddComponent(ceiling_sprite);
			walls[i]->SpriteRef(sprite_ref);

			int colliderRef = -1;
			walls[i]->AddComponent(wall_collider);
			Physics.AddCollider(wall_collider, colliderRef);
			walls[i]->ColliderRef(colliderRef);

			
			walls[i]->isActive(true);
			walls[i]->SetName("Wall "+ std::to_string(i+1));
			AddGameObject(walls[i]);

			colliders[i]->isActive(true);
			AddGameObject(colliders[i]);

		}
	}
}