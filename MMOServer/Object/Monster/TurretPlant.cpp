#include "pch.h"
#include "TurretPlant.hpp"
#include "Storage/GameMap.hpp"

TurretPlant::TurretPlant(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, mmo::TurretPlant, map)
{
	SetHp(20);
	SetPower(2);
	SetAttackRange(5);
}

void TurretPlant::BeginPlay()
{
	Monster::BeginPlay();
	SetAutomove(false);
}

void TurretPlant::Tick()
{
	Monster::Tick();
	if (m_projectile)
	{

	}
}

void TurretPlant::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	if (auto map = GetMap(); map && !m_projectile)
	{
		m_target = std::static_pointer_cast<Player>(target);
		m_targetPosition = target->GetPosition();

		m_projectile = CreateObject(NetObject, mmo::Projectile);
		m_projectile->SetPosition(GetPosition());

		mmo::NotifySpawn spawn;
		mmo::ObjectInfo info;
		info.objectId = m_projectile->GetId();
		info.position = Converter::MakeVector(m_projectile->GetPosition());
		info.type = mmo::Projectile;
		spawn.objects.push_back(info);
		map->Broadcast(&spawn);
	}
}
