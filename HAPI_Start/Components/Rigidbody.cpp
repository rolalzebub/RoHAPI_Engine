#include "Rigidbody.h"
#include "GameObject.h"
#include "TimeManager.h"
namespace RoHAPI {
	void Rigidbody::Start()
	{
		id = RigidbodyC;
		transform = m_parentObject->GetTransform();
	}
	void Rigidbody::Update()
	{
		if (velocity.Length() > maxVelocity.Length()) {
			if (velocity.x < 0)
				velocity.x = -maxVelocity.x;
			else if(velocity.x > 0)
				velocity.x = maxVelocity.x;

			if (velocity.y < 0)
				velocity.y = -maxVelocity.y;
			else if (velocity.y > 0)
				velocity.y = maxVelocity.y;
		}

		transform->Translate(velocity);
	}

	void Rigidbody::ResetVelocity()
	{
		velocity = Vec2d(0.0);
	}

	void Rigidbody::Rebound()
	{
		velocity = Vec2d(-velocity.x, -velocity.y);
	}
}