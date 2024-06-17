#include "pch.h"
#include "Manager.hpp"

#include "NetObjectManager.hpp"
#include "MapManager.hpp"

Manager::Manager()
{
	m_netObject = new NetObjectManager();
	m_map = new MapManager();
}

Manager::~Manager()
{
}

void Manager::Initialize()
{
	m_map->Initialize();
}

NetObjectManager* Manager::Object()
{
	return m_netObject;
}

MapManager* Manager::Map()
{
	return m_map;
}