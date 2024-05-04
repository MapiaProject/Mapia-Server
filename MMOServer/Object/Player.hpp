#pragma once

#include "NetObject.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class GameSession;
class GameMap;

class Player : public NetObject
{
public:
	USE_POOL(Player)
public:
	Player();
	Player(uint64 id);
public:
	void SetSession(std::shared_ptr<GameSession>);
	void SetPosition(Vector2DI position);
	void SetNickname(StringView nickname);
	std::shared_ptr<GameSession> GetSession();
	std::shared_ptr<GameMap> GetMap() const;
	Vector2DI GetPosition() const;
	String GetNickname() const;	

	void EnterMap(std::shared_ptr<GameMap> gameMap);
	void LeaveMap();
private:
	std::weak_ptr<GameSession> m_session;
	std::weak_ptr<GameMap> m_map;
	Vector2DI m_position;
	String m_nickname;
};