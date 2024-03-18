#include "pch.h"
#include "GameRoom.hpp"
#include <Session/GameSession.hpp>
#include <Room/Player.hpp>
#include <Managers/Manager.hpp>
#include <Managers/RoomManager.hpp>

using namespace gen;

void GameRoom::HandleEnter(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto success = false;
	if (gameSession->GetRoom() == nullptr && m_players.size() < MAX_PLAYER)
	{
		success = true;

		auto player = std::make_shared<Player>();
		player->SetSession(gameSession);
		player->SetId(++lastPlayerId);
		m_players[player->GetId()] = player;

		gameSession->SetPlayer(player);
		gameSession->SetRoom(std::static_pointer_cast<Room>(shared_from_this()));

		mmo::NotifyPlayerList list;
		for (const auto& playerData : m_players)
		{
			mmo::PlayerInfo info;
			info.id = playerData.second->GetId();
			info.name = playerData.second->GetName();
			list.playerList.push_back(info);
		}
		Broadcast(&list);
	}
	HandleResult(session.get(), mmo::ERoomEvent::ENTER, success);
}

void GameRoom::HandleLeave(std::shared_ptr<Session> session)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();
	auto success = false;
	if (m_players[player->GetId()])
	{
		success = true;
		m_players.erase(player->GetId());
		gameSession->SetRoom(nullptr);

		if (m_players.size() == 0)
			GManager->GetRoom()->Launch(&RoomManager::DestroyRoom, m_id);

		mmo::NotifyPlayerList list;
		for (const auto& player : m_players)
		{
			mmo::PlayerInfo info;
			info.id = player.second->GetId();
			info.name = player.second->GetName();
			list.playerList.push_back(info);
		}
		Broadcast(&list);
	}
	HandleResult(session.get(), mmo::ERoomEvent::LEAVE, success);
}
