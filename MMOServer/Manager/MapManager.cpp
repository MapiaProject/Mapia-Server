#include "pch.h"
#include "MapManager.hpp"

#include <filesystem>

MapManager::MapManager()
{
	for (auto& iter : std::filesystem::directory_iterator(TEXT("common/generated/maps/")))
	{
		auto map = MapData(action::Split(String(iter.path()), TEXT('/')).back());
		m_mapData[map.GetName()] = map;
	}
}

MapData MapManager::GetMap(String name)
{
	return m_mapData[name];
}

