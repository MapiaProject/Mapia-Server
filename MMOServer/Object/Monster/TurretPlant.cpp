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
}

void TurretPlant::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	auto projectile = GManager->Object()->Create<Projectile>(GetMap(), target->GetPosition());
}
