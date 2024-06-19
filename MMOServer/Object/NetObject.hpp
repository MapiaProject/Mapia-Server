#pragma once

#include "generated/mmo/Enum.gen.hpp"
#include "Manager/NetObjectManager.hpp"

using namespace gen;

class GameObject
{
public:
	GameObject() = default;
	GameObject(mmo::EObjectType type);
	virtual ~GameObject() noexcept { };
public:
	__forceinline mmo::EObjectType GetType() const { return m_objectTy; }
	__forceinline Vector2DF GetPosition() const { return m_position; }
	__forceinline uint32 GetHp() const { return m_hp; }
	__forceinline uint32 GetPower() const { return m_power; }

	__forceinline void SetType(mmo::EObjectType type) { m_objectTy = type; }
	__forceinline void SetPosition(Vector2DF position) { m_position = position; }
	__forceinline void SetHp(uint32 hp) { m_hp = hp; };
	__forceinline void SetPower(uint32 power) { m_power = power; }
protected:
	mmo::EObjectType m_objectTy;
	Vector2DF m_position;
	uint32 m_hp;
	uint32 m_power;
};

class NetObject :
	public std::enable_shared_from_this<NetObject>,
	public GameObject
{
public:
	NetObject();
	NetObject(uint64 id, mmo::EObjectType type);
	virtual ~NetObject() noexcept { }
public:
	__forceinline uint64 GetId() const { return m_objectId; }
	__forceinline void SetId(uint64 id) { m_objectId = id; }
public:
	virtual void BeginPlay() { };
	virtual void Tick() { };
	virtual void OnDestroy();
	virtual void OnDamaged(const std::shared_ptr<NetObject>) { };
public:
	void TakeDamage(const std::shared_ptr<NetObject>& hitter, int32 damage);
private:
	uint64 m_objectId;
};

