#pragma once
#include "Object/NetObject.hpp"

class Monster : public NetObject
{
	enum
	{
		MoveTick = 200
	};
	enum State
	{
		IDLE,
		PATROL,
		FOLLOW,
		ATTACK
	};
public:
	Monster(uint64 id, std::shared_ptr<class GameMap> map);
	virtual ~Monster() noexcept {}
public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void OnDestroy();
	virtual void OnDamaged(const std::shared_ptr<NetObject> attacker);
public:
	void SetAutomove(bool enable);
	bool IsAutomove() const;
	std::shared_ptr<class GameMap> GetMap() const;
private:
	void NextDestination();
	void Attack();
private:
	/* functional */
	std::weak_ptr<class GameMap> m_map;
	bool m_enableAutomove;
	State m_state;

	/* patrol data */
	bool m_patrol;
	int32 m_dir;
	int32 m_dest;
	uint64 m_moveTime;
	uint64 m_nextMoveTime;

	/* Follow */
	std::weak_ptr<class Player> m_target;

	/* attack */
	uint32 m_power;
	float m_attackRange;
};

