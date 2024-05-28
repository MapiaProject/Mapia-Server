#include "pch.h"
#include "NetObject.hpp"

NetObject::NetObject(uint64 id, gen::mmo::EObjectType type) : m_objectId(id), m_objectTy(type)
{
}

NetObject::~NetObject()
{
	Console::Log(Category::Temp, LogType::Debug, TEXT("Destroy"));
}

uint64 NetObject::GetId() const
{
	return m_objectId;
}

void NetObject::SetId(uint64 id)
{
	m_objectId = id;
}
