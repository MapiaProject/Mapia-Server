#include "pch.h"
#include "RoomManager.hpp"

#include "Room.hpp"
#include "Network/Session.hpp"
#include "generated/Protocol.gen.hpp"

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

bool RoomManager::AddRoom(std::shared_ptr<Room> room)
{
	if (m_roomList[room->GetId()] == nullptr)
		m_roomList[room->GetId()] = room;
	else return false;
}

void RoomManager::HandleEnterGame(std::shared_ptr<Session> session)
{
	Vector<std::shared_ptr<Room>> rooms;
	std::transform(m_roomList.begin(), m_roomList.end(), std::back_inserter(rooms), [](const auto& p)
	{
		return p.second;
	});

	gen::NotifyRoomList res;
	for (const auto& room : rooms)
	{
		gen::Room protoRoom;
		protoRoom.id = room->GetId();
		protoRoom.name = room->GetName();
		res.roomList.push_back(protoRoom);
	}
	session->Send(&res);
}

void RoomManager::HandleRoomEvent(std::shared_ptr<Session> session, gen::AddRoomEvent pk)
{
	switch (pk.event)
	{
	case gen::CREATE:
		AddRoom(std::make_shared<Room>(pk.room.name));
		break;
	case gen::ENTER:
		if (auto room = m_roomList[pk.room.id])
			room->Launch(&Room::HandleEnter, session);
		break;
	case gen::LEAVE:
		if (auto room = m_roomList[pk.room.id])
			room->Launch(&Room::HandleLeave, session);
		break;
	}
}
