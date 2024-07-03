#include "pch.h"
#include "GameObject.hpp"

GameObject::GameObject(uint64 id, mmo::EObjectType type) : NetObject(id), m_objectTy(type)
{

}

void GameObject::TakeDamage(const std::shared_ptr<GameObject>& hitter, int32 damage)
{
	m_hp -= damage;
	OnDamaged(hitter);
	if (m_hp <= 0)
	{
		OnDestroy(hitter);
	}
}

NetObject::NetObject() : m_lastTickCount(GetTickCount64())
{
}

NetObject::NetObject(uint64 id) : m_objectId(id)
{
}

void NetObject::Tick()
{
	m_delta = static_cast<decltype(m_delta)>(GetTickCount64() - m_lastTickCount);
	m_lastTickCount = GetTickCount64();
}

void NetObject::OnDestroy(const std::shared_ptr<GameObject>& hitter)
{
	GManager->Object()->RemoveObject(m_objectId);
}