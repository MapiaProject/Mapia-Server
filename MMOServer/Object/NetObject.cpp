#include "pch.h"
#include "NetObject.hpp"

GameObject::GameObject(mmo::EObjectType type) : m_objectTy(type)
{

}

NetObject::NetObject() : GameObject(), m_lastTickCount(GetTickCount64())
{
}

NetObject::NetObject(uint64 id, mmo::EObjectType type) : GameObject(type), m_objectId(id)
{
}

void NetObject::Tick()
{
	m_delta = static_cast<decltype(m_delta)>(GetTickCount64() - m_lastTickCount);
	m_lastTickCount = GetTickCount64();
}

void NetObject::OnDestroy()
{
	GManager->Object()->RemoveObject(m_objectId);
}

void NetObject::TakeDamage(const std::shared_ptr<NetObject>& hitter, int32 damage)
{
	m_hp -= damage;
	OnDamaged(hitter);
	if (m_hp <= 0)
	{
		OnDestroy();
	}
}