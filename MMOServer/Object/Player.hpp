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
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void OnDestroy() override;
	virtual void OnDamaged(const std::shared_ptr<NetObject>) override;
public:	
	void SetSession(std::shared_ptr<GameSession>);
	void SetNickname(StringView nickname);
	std::shared_ptr<GameSession> GetSession();
	std::shared_ptr<GameMap> GetMap() const;
	String GetNickname() const;
	std::shared_ptr<NetObject> GetHitter();

	void EnterMap(std::shared_ptr<GameMap> gameMap);
	void LeaveMap();

	void TryDamage(const std::shared_ptr<NetObject> hitter);
private:
	std::shared_ptr<Player> SharedThis();
private:
	std::weak_ptr<GameSession> m_session;
	std::weak_ptr<GameMap> m_map;
	std::weak_ptr<NetObject> m_hitter;
	String m_nickname;
};