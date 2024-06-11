#include "pch.h"
#include "NetObject.hpp"
#include "Manager/NetObjectManager.hpp"

NetObject::NetObject(uint64 id, gen::mmo::EObjectType type) : m_objectId(id), m_objectTy(type)
{
}

NetObject::~NetObject()
{
}

void NetObject::OnDestroy()
{
	GManager->Object()->RemoveObject(m_objectId);
}

void NetObject::TakeDamage(int32 damage)
{
	m_hp -= damage;
	if (m_hp <= 0)
	{
		OnDestroy();
	}
}
