#pragma once
#include "Collider.h"
namespace RoHAPI {
	class SpriteCollider :public Collider
	{
	private:
		DWORD* mask = nullptr;
		Vec2i maskSize = Vec2i(0);
		int dwordSize = 0;

	public:
		SpriteCollider(GameObject* base) : Collider(base) { id = ColliderC; };
		SpriteCollider() : Collider() { id = ColliderC; };
		virtual ~SpriteCollider();

		void SpriteCollider::GenerateMask(BYTE* imageData, const Rect& rect);
		bool CheckCollider(SharedPtr<SpriteCollider> collider);

		void Start() override;
		void Update() override;
		Rect GetColliderRect()const override;

		DWORD* GetMask() const { return mask; };
		Vec2i GetMaskSize() const { return maskSize; };
		int getDwordSize() const { return dwordSize; };

	};

}