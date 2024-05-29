#include "pch.h"
#include "NetObject.hpp"

NetObject::NetObject(uint64 id, gen::mmo::EObjectType type) : m_objectId(id), m_objectTy(type)
{
}

NetObject::~NetObject()
{
}