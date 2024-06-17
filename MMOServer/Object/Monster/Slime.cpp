#include "pch.h"
#include "Slime.hpp"
#include "Storage/GameMap.hpp"

Slime::Slime(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, map), m_target()
{
	
}

void Slime::BeginPlay()
{
	Monster::BeginPlay();
	EnablePatrol(true);
}

void Slime::Tick()
{
	Monster::Tick();
	if (auto target = m_target.lock(); target && GetIsUsePatrol())
		EnablePatrol(false);
}

void Slime::OnDamaged(const std::shared_ptr<NetObject> attacker)
{
	if (!attacker)
		return;
	m_target = attacker;
}
