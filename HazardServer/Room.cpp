#include "pch.h"
#include "Room.hpp"

#include "Player.hpp"
#include "GameSession.hpp"

#include "Network/Packet.hpp"
#include "Managers/Manager.hpp"

void Room::Broadcast(Packet* pk, uint32 exceptId)
{
	for (const auto& players : m_players)
	{
		auto player = players.second;
		if (player->GetId() == exceptId)
			continue;
		player->GetSession()->Send(pk);
	}
}

void Room::HandleEnter(std::shared_ptr<Session> session)
{
	if (m_players.size() < MAX_PLAYER)
	{
		auto gameSession = std::static_pointer_cast<GameSession>(session);
		auto player = std::make_shared<Player>();
		player->SetId(m_players.size());
		gameSession->SetPlayer(player);
		m_players[player->GetId()] = player;
	}
	else
	{
		gen::RoomEventRes res;
		res.success = false;
		session->Send(&res);
	}
}

void Room::HandleLeave(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();
	if (m_players[player->GetId()])
	{
		m_players.erase(player->GetId());
		if (m_players.size() == 0)
			GManager->GetRoom()->Launch(&RoomManager::DestroyRoom, m_id);
	}
	else
	{
		gen::RoomEventRes res;
		res.success = false;
		session->Send(&res);
	}
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
