#pragma once

#include "generated/mmo/Enum.gen.hpp"
#include "Manager/NetObjectManager.hpp"

using namespace gen;

class BaseObject
{
public:
	BaseObject() = default;
	BaseObject(mmo::EObjectType type);
public:
	__forceinline mmo::EObjectType GetType() const { return m_objectTy; }
	__forceinline Vector2DF GetPosition() const { return m_position; }
	__forceinline int32 GetHp() const { return m_hp; }
	__forceinline void SetType(mmo::EObjectType type) { m_objectTy = type; }
	__forceinline void SetPosition(Vector2DF position) { m_position = position; }
	__forceinline void SetHp(int32 hp) { m_hp = hp; };
protected:
	mmo::EObjectType m_objectTy;
	Vector2DF m_position;
	int32 m_hp;
};

class NetObject :
	public std::enable_shared_from_this<NetObject>,
	public BaseObject
{
public:
	NetObject();
	NetObject(uint64 id, mmo::EObjectType type);
public:
	__forceinline uint64 GetId() const { return m_objectId; }
	__forceinline void SetId(uint64 id) { m_objectId = id; }
public:
	virtual void BeginPlay() { };
	virtual void Tick() { };
	virtual void OnDestroy();
	virtual void OnDamaged(const std::shared_ptr<NetObject> attacker) { };
public:
	void TakeDamage(const std::shared_ptr<NetObject>& attacker, int32 damage);
private:
	uint64 m_objectId;
};

