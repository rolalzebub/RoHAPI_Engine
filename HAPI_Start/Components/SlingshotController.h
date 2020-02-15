#pragma once
#include "Component.h"
namespace RoHAPI {
	class Rigidbody;

	class SlingshotController :
		public Component
	{
	private:

		enum class MouseState{
			Hovering,
			Held
		} current_state = MouseState::Hovering;

		Vec2i mouseClickPos;
		Vec2i mouseReleasePos;
		Vec2d mouseWorldPos;
		double m_slingshotForce = 5;

		int mouseHeight= 5, mouseWidth = 5;

		Rigidbody* rb;

		void Slingshot();

	public:
		void Start() override;
		void Update() override;
		void FixedUpdate() override;


		SlingshotController(GameObject* parentObject_) :Component(parentObject_) {}
		SlingshotController(GameObject* parentObject_, double slingshotForce) : Component(parentObject_) { m_slingshotForce = slingshotForce; }
	};
}
