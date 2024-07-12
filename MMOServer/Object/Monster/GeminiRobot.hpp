#pragma once
#include "Monster.hpp"

class GeminiRobot : public Monster
{
	USE_POOL(GeminiRobot)
public:
	GeminiRobot(uint64, class GameMap* map);
private:
	void BeginPlay() override;
	void Tick() override;
};

