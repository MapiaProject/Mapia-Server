#include "pch.h"
#include "Slime.hpp"
#include "Storage/GameMap.hpp"

Slime::Slime(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, mmo::Slime, map)
{
}

void Slime::BeginPlay()
{
	Monster::BeginPlay();
	SetAutomove(true);
}

void Slime::Tick()
{
	Monster::Tick();
}

void Slime::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	Monster::ProcessAttack(target);
}
