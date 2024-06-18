#pragma once
#include "Thread/JobSerializer.hpp"
#include "Storage/MapData.hpp"

#include "generated/mmo/ServerPacketHandler.gen.hpp"

class NetObject;

class GameMap : public JobSerializer, public MapData
{
	enum
	{
		GameTick = 33, // for 30fps tick rate
		SpawnTick = 5000
	};
public:
	GameMap(StringView path);
	~GameMap();
public:
	void Broadcast(std::span<char> buffer, uint64 ignore = 0);
	void Broadcast(Packet* packet, uint64 ignore = 0);
	void Enter(std::shared_ptr<NetObject> object);
	void Leave(std::shared_ptr<NetObject> object);
	void SpawnMonster();
public:
	HashMap<uint64, std::shared_ptr<class Player>> GetPlayers() const;
	HashMap<uint64, std::shared_ptr<class Monster>> GetMonsters() const;
public:
	void HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move);
	void HandleLocalChat(std::shared_ptr<Session> session, gen::mmo::Chat chat);
	void HandleDamage(std::shared_ptr<Session> session, gen::mmo::AddDamageReq damage);
	void HandleHitStatus(std::shared_ptr<Session> session, gen::mmo::HitStatus hit);
public:
	void BeginPlay();
	void Tick();
private:
	HashMap<uint64, std::shared_ptr<class Player>> m_players;
	HashMap<uint64, std::shared_ptr<class Monster>> m_monsters;
};

