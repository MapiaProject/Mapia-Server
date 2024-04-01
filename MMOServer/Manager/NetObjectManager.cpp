#include "pch.h"
#include "NetObjectManager.hpp"
#include "Session/GameSession.hpp"
#include "Object/Player.hpp"
#include "Manager.hpp"
#include "MapManager.hpp"

NetObjectManager::NetObjectManager() : m_lastId(0)
{
}

void NetObjectManager::HandleEnterGame(std::shared_ptr<Session> session, gen::mmo::EnterGameReq req)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);

	// send enter game success or failure
	gen::mmo::EnterGameRes res;
	res.success = !m_checkAccount[req.uid];
	if (res.success)
	{
		auto player = std::static_pointer_cast<Player>(Create<Player>());
		gameSession->SetPlayer(player);

		player->SetSession(gameSession);
	}
	gameSession->Send(&res);
}
