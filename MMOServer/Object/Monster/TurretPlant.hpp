#pragma once
#include "Monster.hpp"

class TurretPlant : public Monster
{
	USE_POOL(TurretPlant)
	enum
	{
		UPDATE_PROJECTILE_TICK = 50
	};
public:
	TurretPlant(uint64 id, std::shared_ptr<class GameMap> map);
private:
	void BeginPlay() override;
	void Tick() override;
	void ProcessAttack(const std::shared_ptr<NetObject>) override;
private:
	uint64 m_tick;
	std::weak_ptr<class Player> m_target;
	Vector2DF m_targetPosition;
	std::shared_ptr<NetObject> m_projectile;
};

