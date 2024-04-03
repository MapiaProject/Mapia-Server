#pragma once
#include "Thread/JobSerializer.hpp"
#include "Storage/MapData.hpp"

#include "generated/mmo/ServerPacketHandler.gen.hpp"

class GameMap : public JobSerializer, public MapData
{
public:
	GameMap();
	GameMap(StringView path);
	~GameMap();
public:
	void Broadcast(Packet* packet, uint64 ignore);
	Vector<std::shared_ptr<class Player>> Players();
	void AddPlayer(std::shared_ptr<class Player> player);
	void RemovePlayer(std::shared_ptr<class Player> player);
public:
	void HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move);
private:
	HashMap<uint64, std::shared_ptr<class Player>> m_players;
};

