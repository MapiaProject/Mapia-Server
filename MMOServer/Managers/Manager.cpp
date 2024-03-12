#include "pch.h"
#include "Manager.hpp"

#include "RoomManager.hpp"
#include "Room.hpp"
#include "DatabaseManager.hpp"

Manager::Manager()
{
	m_roomManager = std::make_shared<RoomManager>();
	m_roomManager->Launch(&RoomManager::AddRoom, String(TEXT("test1")));
	m_roomManager->Launch(&RoomManager::AddRoom, String(TEXT("test2")));

	m_databaseManager = std::make_shared<DatabaseManager>();
}

Manager::~Manager()
{
	m_roomManager = nullptr;
	m_databaseManager = nullptr;
}