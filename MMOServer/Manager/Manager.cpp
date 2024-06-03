#include "pch.h"
#include "Manager.hpp"

#include "NetObjectManager.hpp"
#include "MapManager.hpp"

Manager::Manager()
{
	m_netObject = MakeShared<NetObjectManager>();
	m_map = MakeShared<MapManager>();
}

Manager::~Manager()
{
}

std::shared_ptr<NetObjectManager> Manager::Object()
{
	return m_netObject;
}

std::shared_ptr<MapManager> Manager::Map()
{
	return m_map;
}