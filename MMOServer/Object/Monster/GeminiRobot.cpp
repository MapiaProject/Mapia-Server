#include "pch.h"
#include "GeminiRobot.hpp"

GeminiRobot::GeminiRobot(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, mmo::GeminiRobot, map)
{
	SetHp(100);
	SetPower(10);
	SetAttackRange(1);
}

void GeminiRobot::BeginPlay()
{
	Monster::BeginPlay();
	SetAutomove(true);
}

void GeminiRobot::Tick()
{
	Monster::Tick();
}
