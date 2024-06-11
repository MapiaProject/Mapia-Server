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
	delete m_netObject;
	delete m_map;
}

NetObjectManager* Manager::Object()
{
	return m_netObject;
}

MapManager* Manager::Map()
{
	return m_map;
}