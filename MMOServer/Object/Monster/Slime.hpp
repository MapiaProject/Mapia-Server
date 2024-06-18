#pragma once
#include "Monster.hpp"

class Slime : public Monster
{
	USE_POOL(Slime)
public:
	Slime(uint64 id, std::shared_ptr<class GameMap> map);
public:
	void BeginPlay() override;
	void Tick() override;
};
