#include "pch.h"
#include "MapManager.hpp"
#include "Session/GameSession.hpp"

#include <filesystem>


MapManager::MapManager()
{
	for (auto& iter : std::filesystem::directory_iterator(TEXT("common/generated/maps/")))
	{
		auto map = MapData(action::Split(String(iter.path()), TEXT('/')).back());
		auto gameMap = std::make_shared<GameMap>(map);
		m_mapData[map.GetName()] = gameMap;
	}
}

std::shared_ptr<GameMap> MapManager::GetMap(String name)
{
	return m_mapData[name];
}

void MapManager::HandleEnter(std::shared_ptr<Session> session, gen::mmo::EnterMapReq packet)
{
	auto gameMap = m_mapData[packet.mapName];

}

	