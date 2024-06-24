#include "pch.h"
#include "TurretPlant.hpp"
#include "Projectile.hpp"

TurretPlant::TurretPlant(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, map)
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
		m_projectile->Tick();
}

void TurretPlant::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	m_projectile = GManager->Object()->Create<Projectile>(target->GetPosition());
	m_projectile->SetPosition(GetPosition());
	m_projectile->BeginPlay();
}
