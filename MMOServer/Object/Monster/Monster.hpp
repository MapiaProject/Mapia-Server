#pragma once
#include "Object/NetObject.hpp"

class Monster : public NetObject
{
	enum
	{
		MoveTick = 150
	};
public:
	Monster(uint64 id, std::shared_ptr<class GameMap> map);
	virtual ~Monster() {}
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
protected:
	std::weak_ptr<class GameMap> m_map;
private:
	void NextDestination();
private:
	int32 m_dir;
	int32 m_dest;
	int64 m_moveTime;
	uint64 m_nextMoveTime;
};

