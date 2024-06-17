#pragma once
#include "Thread/JobSerializer.hpp"
#include "Storage/MapData.hpp"

#include "generated/mmo/ServerPacketHandler.gen.hpp"

class BaseObject;

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
	Vector<std::shared_ptr<class Player>> Players();
	Vector<std::shared_ptr<class Monster>> Monsters();
	void Enter(std::shared_ptr<class Player> player);
	void Leave(std::shared_ptr<class Player> player);
	void SpawnMonster();
public:
	void HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move);
	void HandleLocalChat(std::shared_ptr<Session> session, gen::mmo::Chat chat);
	void HandleDamage(std::shared_ptr<Session> session, gen::mmo::AddDamageReq damage);
public:
	void BeginPlay();
	void Tick();
private:
	HashMap<uint64, std::shared_ptr<BaseObject>> m_objects;
};

