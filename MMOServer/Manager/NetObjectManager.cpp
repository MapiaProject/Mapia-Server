#include "pch.h"
#include "NetObjectManager.hpp"
#include "Session/GameSession.hpp"
#include <Object/Player.hpp>

NetObjectManager::NetObjectManager() : m_lastId(0)
{
}

void NetObjectManager::HandleEnterGameReq(std::shared_ptr<class Session> session, gen::mmo::EnterGameReq req)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = std::static_pointer_cast<Player>(Create<Player>());
	gameSession->SetPlayer(player);
	player->SetSession(gameSession);
	player->SetMap
}
