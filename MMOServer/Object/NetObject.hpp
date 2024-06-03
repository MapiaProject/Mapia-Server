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
	__forceinline Vector2DI GetPosition() const { return m_position; }
	__forceinline uint64 GetId() const { return m_objectId; }
	__forceinline void SetPosition(Vector2DI position) { m_position = position; }
	__forceinline void SetId(uint64 id) { m_objectId = id; }
	__forceinline mmo::EObjectType GetType() const { return m_objectTy; }
public:
	virtual void Tick(float tick) abstract;
protected:
	uint64 m_objectId;
	mmo::EObjectType m_objectTy;
	Vector2DI m_position;
};

