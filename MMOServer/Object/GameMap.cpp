#include "pch.h"
#include "GameMap.hpp"
#include "Player.hpp"
#include "Session/GameSession.hpp"

GameMap::GameMap(MapData mapData) : m_map(mapData.GetMap())
{
}

GameMap::~GameMap()
{
}

const Vector<Vector<Block>>& GameMap::GetMap() const
{
	return m_map;
}

void GameMap::Broadcast(Packet* packet, uint64 ignore)
{
	for (const auto& player : m_players)
	{
		if (player.first != ignore)
			player.second->GetSession()->Send(packet);
	}
}
