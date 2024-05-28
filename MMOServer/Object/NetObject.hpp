#pragma once

#include "generated/mmo/Enum.gen.hpp"

using namespace gen;

class NetObject : public std::enable_shared_from_this<NetObject>
{
public:
	NetObject() = default;
	NetObject(uint64 id, mmo::EObjectType type);
	virtual ~NetObject();
public:
	uint64 GetId() const;
	void SetId(uint64 id);
	__forceinline mmo::EObjectType GetType() const { return m_objectTy; }
public:
	virtual void Update() abstract;
private:
	uint64 m_objectId;
	mmo::EObjectType m_objectTy;
};

