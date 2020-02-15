#include "SlingshotController.h"
#include "Component.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Rigidbody.h"
#include "util_includes.h"
namespace RoHAPI {

	void SlingshotController::Slingshot()
	{
		if (rb != nullptr) {
			Vec2d slingDirection;
			slingDirection.x =  m_parentObject->GetTransform()->GetPosition().x - mouseWorldPos.x;
			slingDirection.y =  m_parentObject->GetTransform()->GetPosition().y - mouseWorldPos.y;

			Vec2d normalized_sling = slingDirection.Normalize();

			rb->AddForce(normalized_sling);
		}
	}

	void SlingshotController::Start()
	{
		id = SlingshotC;
		rb = m_parentObject->GetComponent<Rigidbody>(RigidbodyC);
	}

	void SlingshotController::Update()
	{
		/*if (Input.GetLeftMouseButton()) {
			if (current_state == MouseState::Hovering) {
				mouseClickPos = Input.GetMousePosition();
				Vec2d screenPos = Renderer.GetScreenPosition();
				Vec2d pos = m_parentObject->GetTransform()->GetPosition();
				Vec2d playerPos = m_parentObject->GetTransform()->GetPosition();
				

				Rect playerLocalRect = Physics.GetCollider(m_parentObject->ColliderRef())->GetColliderRect();
				Rect mouse{ (double) mouseClickPos.y + screenPos.y, (double)mouseClickPos.y + screenPos.y + mouseHeight, (double) mouseClickPos.x + screenPos.x, (double) mouseClickPos.x + screenPos.x + mouseWidth };
				Rect player{ (double)playerPos.y + playerLocalRect.GetRectDims().top, playerPos.y + playerLocalRect.GetRectDims().bottom, playerPos.x + playerLocalRect.GetRectDims().left, playerPos.x + playerLocalRect.GetRectDims().right };


				if(mouse.Intersects(player))
					current_state = MouseState::Held;
			}
		}
		else {
			if (current_state == MouseState::Held) {
				Vec2d screenPos = Renderer.GetScreenPosition();
				mouseReleasePos = Input.GetMousePosition();
				mouseWorldPos.x = mouseReleasePos.x + screenPos.x;
				mouseWorldPos.y = mouseReleasePos.y + screenPos.y;
				Slingshot();
				current_state = MouseState::Hovering;
			}
		}*/

	}
	void SlingshotController::FixedUpdate()
	{
		
	}
}