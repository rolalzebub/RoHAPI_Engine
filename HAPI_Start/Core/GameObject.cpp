#include "GameObject.h"
#include "Transform.h"
#include "Spritesheet.h"
#include "Component.h"
namespace RoHAPI
{

	GameObject::~GameObject()
	{
		DeleteObject();
	}

	SharedPtr<Transform> GameObject::GetTransform()
	{
		return m_transform;
	}

	SharedPtr<GameObject> GameObject::GetChildByName(std::string name)
	{
		for (auto child : m_children)
			if (child->GetName() == name)
				return child;

		return nullptr;
	}

	void GameObject::Explode()
	{
		//Game.SpawnExplosion(transform->GetPosition());
		isActive(false);
	}

	template <typename T>
	void GameObject::UpdateChildren(Vec2<T> parentPos)
	{
		for (auto c : m_children)
		{
			c->UpdateChildren(parentPos);
		}
		m_transform->SetPosition(parentPos);
	}

	void GameObject::OnEnable()
	{
	}

	void GameObject::Start()
	{
	}

	void GameObject::Update()
	{
		if (m_children.size() > 0)
			UpdateChildren(m_transform->GetPosition());
	}

	void GameObject::FixedUpdate()
	{
	}

	void GameObject::Stop()
	{
		for (auto c : m_children)
			c->Stop();
	}

	void GameObject::AddComponent(SharedPtr<Component> comp)
	{
		comp->SetParent(this);
		m_components.push_back(comp);
	}

	bool GameObject::HasComponent(int id)
	{
		for (auto comp : m_components)
		{
			if (comp->GetID() == id)
				return true;
		}

		return false;
	}

	void GameObject::AddChild(SharedPtr<GameObject> child)
	{
		m_children.push_back(child);
	}

	std::vector<SharedPtr<GameObject>>& GameObject::GetChildren()
	{
		return m_children;
	}

	void GameObject::isActive(bool active_)
	{
		for (auto c : m_components)
			c->IsEnabled(active_);
		for (auto child : m_children)
			child->isActive(active_);
		if (active_)
			OnEnable();
		active = active_;
	}

	void GameObject::DeleteObject()
	{
		for (auto c : m_children)
		{
			c->DeleteObject();
			c->Stop();
		}
		collidingObjects.clear();

		for (auto c : m_components)
			c->Stop();
	}


	void GameObject::Destroy()
	{
		DeleteObject();
	}
}