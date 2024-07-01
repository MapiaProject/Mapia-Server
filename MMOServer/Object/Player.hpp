#pragma once

#include "NetObject.hpp"
#include "Storage/Datasheet.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class GameSession;
class GameMap;

class Inventory
{
public:
	Inventory() = default;
public:
	List<ItemData> items;
};

class Player : public NetObject
{
	USE_POOL(Player)
public:
	Player(uint64 id);
public:
	/* Events */
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void OnDestroy(const std::shared_ptr<NetObject>&) override;
	virtual void OnDamaged(const std::shared_ptr<NetObject>) override;
public:
	/* Get / Set */
	void SetSession(std::shared_ptr<GameSession>);
	void SetNickname(StringView nickname);
	std::shared_ptr<GameSession> GetSession();
	std::shared_ptr<GameMap> GetMap() const;
	String GetNickname() const;
	std::shared_ptr<NetObject> GetHitter();
public:
	/* Interactions */
	void EnterMap(std::shared_ptr<GameMap> gameMap);
	void LeaveMap();

	void TryDamage(const std::shared_ptr<NetObject> hitter);

	void ObtainItem(Vector<ItemData> item);
public:
	/* Skills */
	void Airborne() const;
private:
	std::shared_ptr<Player> SharedThis();
private:
	uint16 m_level;

	std::weak_ptr<GameSession> m_session;
	std::weak_ptr<GameMap> m_map;
	std::weak_ptr<NetObject> m_hitter;
	String m_nickname;
	
	int m_lastPosX;
	bool m_isLookAtRight;

	SkillData m_airborne;
};