#include "pch.h"
#include "NetObjectManager.hpp"
#include "Session/GameSession.hpp"
#include "Object/Player.hpp"
#include "Manager.hpp"
#include "AccountManager.hpp"

NetObjectManager::NetObjectManager() : m_lastId(0)
{
}

void NetObjectManager::HandleEnterGame(std::shared_ptr<Session> session, gen::mmo::EnterGameReq req)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	const auto& nickname = GManager->Account()->GetNickname(req.uid);

	// send enter game success or failure
	gen::mmo::EnterGameRes res;
	res.success = !m_checkAccount[req.uid];
	res.success &= nickname.has_value();
	if (res.success)
	{
		auto player = std::static_pointer_cast<Player>(Create<Player>());
		player->SetNickname(nickname.value());
		gameSession->SetPlayer(player);

		player->SetSession(gameSession);
	}
	gameSession->Send(&res);
}
