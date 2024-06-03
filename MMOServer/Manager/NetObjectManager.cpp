#include "pch.h"
#include "NetObjectManager.hpp"
#include "Session/GameSession.hpp"
#include "Object/Player.hpp"
#include "Manager.hpp"

NetObjectManager::NetObjectManager() : m_lastId(0)
{
}

void NetObjectManager::HandleEnterGame(std::shared_ptr<Session> session, gen::mmo::EnterGameReq req)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	const auto& nickname = req.name;

	// send enter game success or failure
	gen::mmo::EnterGameRes res;
	res.success = true;
	if (res.success)
	{
		auto player = Create<Player>();
		player->SetNickname(nickname);
		gameSession->SetPlayer(player);

		player->SetSession(gameSession);
	}
	gameSession->Send(&res, true);
}

void NetObjectManager::HandleDirectChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto target = std::static_pointer_cast<Player>(m_objects[chat.targetId]);

	gen::mmo::NotifyChat notifyChat;
	notifyChat.senderName = gameSession->GetPlayer()->GetNickname();
	notifyChat.message = chat.message;

	target->GetSession()->Send(&notifyChat, true);
}

void NetObjectManager::HandleAllChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto sender = gameSession->GetPlayer();

	gen::mmo::NotifyChat notifyChat;
	notifyChat.senderName = sender->GetNickname();
	notifyChat.message = chat.message;

	BroadcastAll(&notifyChat, sender->GetId());
}

void NetObjectManager::BroadcastAll(Packet* packet, uint64 ignore)
{
	for (const auto& obj : m_objects)
	{
		if (auto player = std::static_pointer_cast<Player>(obj.second))
			if (player->GetId() != ignore) player->GetSession()->Send(packet);
	}
}
