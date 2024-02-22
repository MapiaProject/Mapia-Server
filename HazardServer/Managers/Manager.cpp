#include "pch.h"
#include "Manager.hpp"

#include "Room.hpp"

std::unique_ptr<Manager> GManager = std::make_unique<Manager>();

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::MakeRoom(String id, String name)
{
	if(!m_roomList[id])
		m_roomList.insert({ id, new Room(name)});
}

void Manager::DestroyRoom(String id)
{
	auto* room = m_roomList[id];
	if (room)
		delete m_roomList[id];
}

Vector<String> Manager::GetRoomList()
{
	return Vector<String>();
}
