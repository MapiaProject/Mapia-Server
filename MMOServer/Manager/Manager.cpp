#include "pch.h"
#include "Manager.hpp"

#include "NetObjectManager.hpp"
#include "MapManager.hpp"

Manager::Manager()
{
	m_netObject = std::make_shared<NetObjectManager>();
	m_map = std::make_shared<MapManager>();
}

Manager::~Manager()
{
}

std::shared_ptr<NetObjectManager> Manager::NetObject()
{
	return m_netObject;
}

std::shared_ptr<MapManager> Manager::Map()
{
	return m_map;
}