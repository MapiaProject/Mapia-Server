#pragma once
#include "Object/NetObject.hpp"

class Monster : public NetObject
{
	enum
	{
		MoveTick = 200
	};
public:
	Monster(uint64 id, std::shared_ptr<class GameMap> map);
	virtual ~Monster() {}
public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void OnDestroy();
	virtual void OnDamaged(const std::shared_ptr<NetObject> attacker);
public:
	void EnableAutomove(bool enable);
	std::shared_ptr<class GameMap> GetMap() const;
	bool GetEnabledAutomove();
private:
	void NextDestination();
private:
	std::weak_ptr<class GameMap> m_map;
	bool m_enableAutomove;

	/* patrol data */
	bool m_patrol;
	int32 m_dir;
	int32 m_dest;
	uint64 m_moveTime;
	uint64 m_nextMoveTime;

	/* Follow */
	std::weak_ptr<class NetObject> m_target;
};

