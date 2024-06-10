#pragma once
#include "Monster.hpp"

class Slime : public Monster
{
public:
	Slime(uint64 id, std::shared_ptr<class GameMap> map);
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};

