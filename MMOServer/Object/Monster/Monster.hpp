#pragma once
#include "Object/NetObject.hpp"

class Monster : public NetObject
{
	friend class GameMap;

	enum State
	{
		IDLE,
		PATROL,
		FOLLOW,
		ATTACK,
		FAINT
	};
	enum LogicTick
	{
		FAINT_TIME = 800
	};
public:
	Monster(uint64 id, mmo::EObjectType type, std::shared_ptr<class GameMap> map);
	virtual ~Monster() noexcept {}
protected:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void OnDestroy(const std::shared_ptr<NetObject>& hitter);
	virtual void OnDamaged(const std::shared_ptr<NetObject> hitter);
	virtual void ProcessAttack(const std::shared_ptr<NetObject> target);
public:
	/* Movement */
	void SetAutomove(bool enable);
	bool IsAutomove() const;

	/* Tick data */
	uint64 GetAttackTick() const;
	uint64 GetMoveTick() const;
	void SetAttackTick(uint64);
	void SetMoveTick(uint64);

	/* Functional */
	std::shared_ptr<class GameMap> GetMap() const;
	void SetAttackRange(float range);
	float GetAttackRange() const;
public:
	void Faint(int32 power);
private:
	void NextDestination();
	void Attack();
private:
	/* delay data */
	uint64 m_moveTick = 200;
	uint64 m_attackTick = 500;
	uint64 m_moveTime;
	uint64 m_nextMoveTime;
	uint64 m_attackTime;

	/* functional */
	std::weak_ptr<class GameMap> m_map;
	bool m_enableAutomove;
	State m_state;
	float m_attackRange;

	/* patrol data */
	bool m_patrol;
	int32 m_dir;
	int32 m_dest;

	/* Follow */
	std::weak_ptr<class Player> m_target;

	uint64 m_endFaintTick;
};

