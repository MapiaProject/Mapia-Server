#include "pch.h"
#include "NetObject.hpp"

BaseObject::BaseObject(mmo::EObjectType type) : m_objectTy(type)
{

}

NetObject::NetObject() : BaseObject()
{
}

NetObject::NetObject(uint64 id, mmo::EObjectType type) : BaseObject(type), m_objectId(id)
{
}

void NetObject::OnDestroy()
{
	GManager->Object()->RemoveObject(m_objectId);
}

void NetObject::TakeDamage(const std::shared_ptr<NetObject>& attacker, int32 damage)
{
	m_hp -= damage;
	OnDamaged(attacker);
	if (m_hp <= 0)
	{
		OnDestroy();
	}
}
