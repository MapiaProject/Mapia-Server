#include "pch.h"
#include "NetObject.hpp"

NetObject::NetObject(uint64 id) : m_objectId(id)
{
}

uint64 NetObject::GetId() const
{
	return m_objectId;
}

void NetObject::SetId(uint64 id)
{
	m_objectId = id;
}
