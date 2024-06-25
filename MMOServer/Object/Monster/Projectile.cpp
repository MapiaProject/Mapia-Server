#include "pch.h"
//#include "Projectile.hpp"
//#include "Storage/GameMap.hpp"
//
//Projectile::Projectile(uint64 id, const std::shared_ptr<GameMap> map, const std::shared_ptr<NetObject> target)
//	: NetObject(id, mmo::EObjectType::Projectile), m_map(map), m_targetObject(target)
//{
//	m_targetPos = target->GetPosition();
//}
//
//void Projectile::BeginPlay()
//{
//}
//
//void Projectile::Tick()
//{
//	NetObject::Tick();
//	if ((m_targetPos - GetPosition()).Length() >= 0.2f)
//	{
//		auto dir = (m_targetPos - GetPosition()).Normalize();
//		m_position += dir * GetDeltatime();
//	}
//	else
//	{
//		if (auto target = m_targetObject.lock(); target && (target->GetPosition() - GetPosition()).Length() < 0.2f)
//		{
//			mmo::NotifyDamaged damage;
//			damage.damageResult.damage = GetPower();
//			damage.damageResult.objectId = target->GetId();
//			if (auto map = m_map.lock())
//				map->Broadcast(&damage);
//		}
//		delete this;
//	}
//}
