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

void RoomManager::AddRoom(String name)
{
	auto newRoom = Room::Create(++m_lastId, name);
	newRoom->m_manager = std::static_pointer_cast<RoomManager>(shared_from_this());
	m_roomList[newRoom->GetId()] = newRoom;
}

void RoomManager::DestroyRoom(uint32 id)
{
	if (m_roomList[id])
		m_roomList.erase(id);
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

void RoomManager::HandleRoomEvent(std::shared_ptr<Session> session, gen::RoomEventReq pk)
{
	gen::RoomEventRes res;
	res.event = pk.event;
	res.success = false;
	switch (pk.event)
	{
		case gen::ENTER:
		{
			if (auto room = m_roomList[pk.room.id])
			{
				room->Launch(&Room::HandleEnter, session);
			}
			else session->Send(&res);
			break;
		}
		case gen::LEAVE:
		{
			if (auto room = m_roomList[pk.room.id])
				room->Launch(&Room::HandleLeave, session);
			else session->Send(&res);
			break;
		}
		case gen::CREATE:
		{
			AddRoom(pk.room.name);
			res.success = false;
			session->Send(&res);
			break;
		}
	}
}
