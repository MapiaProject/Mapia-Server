#pragma once
#include "Storage/MapData.hpp"

class GameMap : private MapData
{
public:
	GameMap(MapData mapData);
	~GameMap();
public:
	const Vector<Vector<Block>>& GetMap() const;
	void Broadcast(Packet* packet, uint64 ignore);
	Vector<std::shared_ptr<class Player>> Players();
private:
	HashMap<uint64, std::shared_ptr<class Player>> m_players;
	Vector<Vector<Block>> m_map;
};

