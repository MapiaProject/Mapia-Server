#pragma once
#include "Thread/JobSerializer.hpp"
#include "Storage/MapData.hpp"

#include "generated/mmo/ServerPacketHandler.gen.hpp"

class GameMap : public JobSerializer, public MapData
{
	enum
	{
		TickDelta = 32
	};
public:
	GameMap();
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
public:
	void Tick();
private:
	HashMap<uint64, std::shared_ptr<class NetObject>> m_objects;
	uint64 m_lastTick;
};

