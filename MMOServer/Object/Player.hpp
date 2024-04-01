#pragma once

#include "NetObject.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class GameSession;
class GameMap;

class Player : public NetObject
{
public:
	Player(uint64 id);
public:
	void SetSession(std::shared_ptr<GameSession>);
	void SetMap(std::shared_ptr<GameMap>);
	void SetPosition(Vector2DI position);
	std::shared_ptr<GameSession> GetSession();
	std::shared_ptr<GameMap> GetMap();
	Vector2DI GetPosition() const;
private:
	std::weak_ptr<GameSession> m_session;
	std::weak_ptr<GameMap> m_map;
	Vector2DI m_position;
};

