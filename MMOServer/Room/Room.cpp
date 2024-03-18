#include "pch.h"
#include "Room.hpp"

#include "Player.hpp"
#include "Session/GameSession.hpp"

#include "Network/Packet.hpp"
#include "Managers/Manager.hpp"

using namespace gen;

void Room::Broadcast(Packet* pk, uint32 exceptId)
{
	for (const auto& playerData : m_players)
	{
		auto player = playerData.second;
		if (player->GetId() == exceptId)
			continue;
		player->GetSession()->Send(pk);
	}
}

void Room::HandleEnter(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = std::make_shared<Player>();
	player->SetSession(gameSession);
	player->SetId(++lastPlayerId);
	m_players[player->GetId()] = player;
		
	gameSession->SetPlayer(player);
}

void Room::HandleLeave(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();
	m_players[player->GetId()] = nullptr;
}

void Room::HandleResult(Session* session, mmo::ERoomEvent event, bool success)
{
	mmo::RoomEventRes res;
	res.event = event;
	res.success = success;
	session->Send(&res);
}

std::shared_ptr<Room> Room::Create(uint32 id, StringView name)
{
	auto newRoom = std::make_shared<Room>();
	newRoom->m_id = id;
	newRoom->m_name = name;
	return newRoom;
}

void Room::SetId(uint32 id)
{
	m_id = id;
}

void Room::SetName(StringView name)
{
	m_name = name;
}
