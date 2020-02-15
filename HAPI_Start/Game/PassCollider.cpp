#include "PassCollider.h"
#include "Sprite.h"
#include "Collider.h"
#include "RenderManager.h"
namespace RoHAPI {
	PassCollider::PassCollider()
	{
		GameObject();

		SharedPtr<Sprite> collider_sprite = MakeSharedPtr<Sprite>(this);
		collider_sprite->CreateColouredBlock(Vec2i(80, 80), HAPI_TColour(173, 216, 230));

		int coll_spriteRef;
		AddComponent(collider_sprite);
		Renderer.AddSprite(collider_sprite, coll_spriteRef);
		SpriteRef(coll_spriteRef);

		SharedPtr<Collider> collider = MakeSharedPtr<Collider>(this);
		collider->SetColliderRect(collider_sprite->GetSpriteDims());

		SetName("Collider ");

		AddComponent(collider_sprite);

		AddComponent(collider);
	}
}