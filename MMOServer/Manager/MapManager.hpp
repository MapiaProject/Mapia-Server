#pragma once

#include "Storage/MapData.hpp"

class MapManager
{
public:
	MapManager();
public:
	MapData GetMap(String name);
private:
	HashMap<String, MapData> m_mapData;
};

