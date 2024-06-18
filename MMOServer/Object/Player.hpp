#pragma once

#include "NetObject.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class GameSession;
class GameMap;

class Player : public NetObject
{
	USE_POOL(Player)
public:
	Player() noexcept;
	Player(uint64 id);
public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void OnDestroy();
public:	
	void SetSession(std::shared_ptr<GameSession>);
	void SetNickname(StringView nickname);
	std::shared_ptr<GameSession> GetSession();
	std::shared_ptr<GameMap> GetMap() const;
	String GetNickname() const;	

	void EnterMap(std::shared_ptr<GameMap> gameMap);
	void LeaveMap();
private:
	std::weak_ptr<GameSession> m_session;
	std::weak_ptr<GameMap> m_map;
	String m_nickname;
};