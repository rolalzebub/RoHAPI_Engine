#pragma once
#include "util_includes.h"
namespace RoHAPI {
	class GameObject;
	class Component
	{
	protected:
		
		GameObject* m_parentObject;
		bool enabled = true;
		int id = 0;
		virtual SharedPtr<Component> CloneImpl() const { return SharedPtr<Component>(new Component(*this)); };

	public:
		Component() {};
		Component(GameObject* parentObject_) : m_parentObject(parentObject_) {};
		~Component() = default;

		virtual void Start() {};
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void Stop() {};

		int GetID() { return id; };
		const bool IsEnabled() { return enabled; };
		void IsEnabled(const bool enabled_) { enabled = enabled_; };
		GameObject* GetParent() { return m_parentObject; };
		void SetParent(GameObject* parentObj) {
			m_parentObject = parentObj;
		}
	};

#define TransformC 0
#define RigidbodyC 1
#define SpriteC 2
#define SpriteColliderC 3
#define SpritesheetC 4
#define PointGravityC 5
#define AnimationC 6
#define SlingshotC 7
}
