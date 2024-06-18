#include "pch.h"
#include "NetObject.hpp"

GameObject::GameObject(mmo::EObjectType type) : m_objectTy(type)
{

}

NetObject::NetObject() : GameObject()
{
}

NetObject::NetObject(uint64 id, mmo::EObjectType type) : GameObject(type), m_objectId(id)
{
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
