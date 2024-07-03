#pragma once
#include "Monster.hpp"

class Slime : public Monster
{
	USE_POOL(Slime)
public:
	Slime(uint64 id, std::shared_ptr<class GameMap> map);
private:
	void BeginPlay() override;
	void Tick() override;
	void ProcessAttack(const std::shared_ptr<GameObject>) override;
};
