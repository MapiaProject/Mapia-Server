#pragma once
#include "Monster.hpp"

class TurretPlant : public Monster
{
	USE_POOL(TurretPlant)
public:
	TurretPlant(uint64 id, std::shared_ptr<class GameMap> map);
private:
	void BeginPlay() override;
	void Tick() override;
	void OnAttack(const std::shared_ptr<NetObject>) override;
};

