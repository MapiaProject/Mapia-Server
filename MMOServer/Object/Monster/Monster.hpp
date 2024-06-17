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
public:
	void EnablePatrol(bool enable);
	std::shared_ptr<class GameMap> GetMap() const;
private:
	void NextDestination();
private:
	std::weak_ptr<class GameMap> m_map;

	uint64 m_sendMoveTime;

	/* patrol data */
	bool m_usePatrol;
	int32 m_dir;
	int32 m_dest;
	uint64 m_moveTime;
	uint64 m_nextMoveTime;
};

