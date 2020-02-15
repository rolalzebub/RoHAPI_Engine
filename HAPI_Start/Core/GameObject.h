#pragma once
#include "util_includes.h"
#include "Component.h"
#include "Transform.h"
namespace RoHAPI {
	struct CollisionInfo {

		GameObject* collided_object;
		Vec2d collisionPoint;
	};

		class GameObject
		{
		protected:
			std::vector<SharedPtr<Component>> m_components;
			int m_spriteIndex = -1;
			int m_spritesheetIndex = -1;
			int m_colliderIndex = -1;
			std::vector<SharedPtr<GameObject>> m_children;
			GameObject* m_parent = nullptr;

			int id = 0;
			bool isColliding = false;

			SharedPtr<Transform> m_transform;
			std::string m_name = "";
			std::string m_tag = "default";
			bool active = false;
			std::vector<GameObject*> collidingObjects;

			template<typename T>
			void UpdateChildren(Vec2<T> parentPos);
			void DeleteObject();

			virtual void Explode();
		public:
			GameObject() { m_transform = MakeSharedPtr<Transform>(); AddComponent(m_transform); };
			GameObject(int id_) { m_transform = MakeSharedPtr<Transform>(); AddComponent(m_transform); } 
			~GameObject();

			virtual void OnEnable();
			virtual void Start();
			virtual void Update();
			virtual void FixedUpdate();
			virtual void Stop();

			template<typename T>
			T* GetComponent(int id)
			{
				for (auto comp : m_components)
				{
					if (comp->GetID() == id)
						return (T*)comp.get();
				}
				return nullptr;
			}
			void AddComponent(SharedPtr<Component> comp);
			bool HasComponent(int id);

			void AddChild(SharedPtr<GameObject> child);
			std::vector<SharedPtr<GameObject>>& GetChildren();
			void AddParent(GameObject* parent) { m_parent = parent; }

			void SetName(const std::string& newName) { m_name = newName; };

			SharedPtr<Transform> GetTransform();
			SharedPtr<GameObject> GetChildByName(std::string name);

			void SetID(const int id_) { id = id_; };
			const int GetID() { return id; };
			const bool isActive() { return active; };
			void isActive(bool active_);

			void SpriteRef(const int ref) { m_spriteIndex = ref; };
			void SpriteSheetRef(const int ref) { m_spritesheetIndex = ref; };
			void ColliderRef(const int ref) { m_colliderIndex = ref; };

			int SpriteRef() const { return m_spriteIndex; };
			int SpriteSheetRef() const { return m_spritesheetIndex; };
			int ColliderRef() const { return m_colliderIndex; };
			
			std::string GetName() const { return m_name; };

			virtual void OnCollisionEnter(CollisionInfo collidedObject) {};
			virtual void OnCollisionStay(CollisionInfo collidedObject) {};
			virtual void OnCollisionExit(CollisionInfo collidedObject) {};

			bool Colliding() const { return isColliding; };
			void Colliding(bool colliding) { isColliding = colliding; };

			void Tag(std::string tag) { m_tag = tag; }
			std::string Tag() const { return m_tag; }

			void Destroy();

		};
}