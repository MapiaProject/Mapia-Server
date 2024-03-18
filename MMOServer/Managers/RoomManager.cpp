#include "pch.h"
#include "RoomManager.hpp"

#include "Room/GameRoom.hpp"
#include "Network/Session.hpp"
#include "generated/mmo/Protocol.gen.hpp"

using namespace gen;

RoomManager::RoomManager() : m_lobby(std::make_shared<Room>())
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::AddRoom(String name)
{
	auto newRoom = std::make_shared<GameRoom>();
	newRoom->SetId(++m_lastId);
	newRoom->SetName(name);
	m_roomList[newRoom->GetId()] = newRoom;
}

void RoomManager::DestroyRoom(uint32 id)
{
	if (m_roomList[id])
		m_roomList.erase(id);
}

void RoomManager::HandleEnterGame(std::shared_ptr<Session> session)
{
	m_lobby->Launch(&Room::HandleEnter, session);

	Vector<std::shared_ptr<Room>> rooms;
	std::transform(m_roomList.begin(), m_roomList.end(), std::back_inserter(rooms), [](const auto& p)
	{
		return p.second;
	});

	gen::mmo::NotifyRoomList res;
	for (const auto& room : rooms)
	{
		mmo::Room protoRoom;
		protoRoom.id = room->GetId();
		protoRoom.name = room->GetName();
		res.roomList.push_back(protoRoom);
	}
	session->Send(&res);
}

void RoomManager::HandleRoomEvent(std::shared_ptr<Session> session, mmo::RoomEventReq pk)
{
	mmo::RoomEventRes res;
	res.event = pk.event;
	res.success = false;
	switch (pk.event)
	{
		case mmo::ERoomEvent::ENTER:
		{
			if (auto room = m_roomList[pk.room.id])
			{
				room->Launch(&GameRoom::HandleEnter, session);
			}
			else session->Send(&res);
			break;
		}
		case mmo::ERoomEvent::LEAVE:
		{
			if (auto room = m_roomList[pk.room.id])
				room->Launch(&GameRoom::HandleLeave, session);
			else session->Send(&res);
			break;
		}
		case mmo::ERoomEvent::CREATE:
		{
			AddRoom(pk.room.name);
			res.success = false;
			session->Send(&res);
			break;
		}
	}
}
