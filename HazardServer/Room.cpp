#include "pch.h"
#include "Room.hpp"

#include "Player.hpp"
#include "GameSession.hpp"

#include "Network/Packet.hpp"
#include "Managers/Manager.hpp"

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
	auto success = false;
	if (gameSession->GetRoom() == nullptr && m_players.size() < MAX_PLAYER)
	{
		Console::Log(LogServer, Debug, TEXT("ENTER"));
		success = true;

		auto player = std::make_shared<Player>();
		player->SetId(++lastPlayerId);
		m_players[player->GetId()] = player;

		gameSession->SetPlayer(player);
		gameSession->SetRoom(std::static_pointer_cast<Room>(shared_from_this()));
		
		gen::NotifyPlayerList list;
		for (const auto& player : m_players)
		{
			gen::PlayerInfo info;
			info.id = player.second->GetId();
			info.name = player.second->GetName();
			list.playerList.push_back(info);
		}
		Broadcast(&list, player->GetId());
	}
	HandleResult(session.get(), gen::ENTER, success);
}

void Room::HandleLeave(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();
	auto success = false;
	if (m_players[player->GetId()])
	{
		success = true;
		Console::Log(LogServer, Debug, TEXT("LEAVE"));
		m_players.erase(player->GetId());
		if (m_players.size() == 0)
			GManager->GetRoom()->Launch(&RoomManager::DestroyRoom, m_id);
		
		gen::NotifyPlayerList list;
		for (const auto& player : m_players)
		{
			gen::PlayerInfo info;
			info.id = player.second->GetId();
			info.name = player.second->GetName();
			list.playerList.push_back(info);
		}
		Broadcast(&list);
	}
	HandleResult(session.get(), gen::LEAVE, success);
}

void Room::HandleResult(Session* session, gen::ERoomEvent event, bool success)
{
	gen::RoomEventRes res;
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
