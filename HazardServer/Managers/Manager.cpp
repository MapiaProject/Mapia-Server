#include "pch.h"
#include "Manager.hpp"

#include "RoomManager.hpp"
#include "Room.hpp"

Manager* GManager = new Manager;

Manager::Manager()
{
	m_roomManager = std::make_shared<RoomManager>();
	m_roomManager->Launch(&RoomManager::AddRoom, std::make_shared<Room>(TEXT("test1")));
	m_roomManager->Launch(&RoomManager::AddRoom, std::make_shared<Room>(TEXT("test2")));
}

Manager::~Manager()
{
	m_roomManager = nullptr;
}