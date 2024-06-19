#include "pch.h"
#include "TurretPlant.hpp"

TurretPlant::TurretPlant(uint64 id, std::shared_ptr<class GameMap> map)
	: Monster(id, map)
{
	SetHp(20);
	SetPower(2);
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

void TurretPlant::OnAttack(const std::shared_ptr<NetObject> target)
{
	Monster::OnAttack(target);
}
