#pragma once
#include "Monster.hpp"

class GeminiRobot : public Monster
{
	USE_POOL(GeminiRobot)
public:
	GeminiRobot(uint64, std::shared_ptr<class GameMap>);
private:
	void BeginPlay() override;
	void Tick() override;
};

