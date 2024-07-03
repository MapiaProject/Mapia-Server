#pragma once

#include "generated/mmo/Enum.gen.hpp"
#include "Manager/ObjectManager.hpp"

#define CreateObject(Type, ...) GManager->Object()->Create<Type>(__VA_ARGS__)

using namespace gen;

class NetObject
{
	USE_POOL(NetObject)
public:
	NetObject();
	NetObject(uint64 id);
	virtual ~NetObject() noexcept { }
public:
	__forceinline uint64 GetId() const { return m_objectId; }
	__forceinline void SetId(uint64 id) { m_objectId = id; }
public:
	virtual void BeginPlay() { };
	virtual void Tick();
	virtual void OnDestroy(const std::shared_ptr<class GameObject>& hitter);
public:
	bool operator<(const NetObject& object)
	{
		return m_objectId > object.GetId();
	}
protected:
	float GetDeltatime() const { return m_delta / 1000.f; }
private:
	uint64 m_objectId;
	uint64 m_lastTickCount;
	uint32 m_delta;
};

class GameObject :
	public NetObject,
	public std::enable_shared_from_this<GameObject>
{
public:
	GameObject() = default;
	GameObject(uint64 id, mmo::EObjectType type);
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
	virtual void OnDamaged(const std::shared_ptr<GameObject>) { };
public:
	void TakeDamage(const std::shared_ptr<GameObject>& hitter, int32 damage);
protected:
	mmo::EObjectType m_objectTy;
	Vector2DF m_position;
	uint32 m_hp;
	uint32 m_power;
};

