#include "pch.h"
#include "Manager.hpp"

#include "NetObjectManager.hpp"
#include "MapManager.hpp"
#include "AccountManager.hpp"

Manager::Manager()
{
	m_netObject = std::make_shared<NetObjectManager>();
	m_map = std::make_shared<MapManager>();
	m_accountManager = std::make_shared<AccountManager>();
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

std::shared_ptr<AccountManager> Manager::Account()
{
	return m_accountManager;
}