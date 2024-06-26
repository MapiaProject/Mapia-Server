#include "pch.h"
#include "ObjectManager.hpp"
#include "Session/GameSession.hpp"
#include "Object/Player.hpp"
#include "Manager.hpp"

ObjectManager::ObjectManager() : m_lastId(0)
{
}

void ObjectManager::Initialize()
{
}

void ObjectManager::RemoveObject(uint64 id)
{
	if (auto& object = m_objects[id])
		object = nullptr;
}

std::shared_ptr<NetObject> ObjectManager::GetObjectById(uint64 id)
{
	return m_objects[id];
}

void ObjectManager::HandleEnterGame(std::shared_ptr<Session> session, gen::mmo::EnterGameReq req)
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

void ObjectManager::HandleDirectChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	for (const auto& [_, object] : m_objects)
	{
		if (object->GetType() == mmo::EObjectType::PLAYER)
		{
			if (auto player = std::static_pointer_cast<Player>(object))
			{
				if (player->GetNickname() == chat.targetName)
				{
					gen::mmo::NotifyChat notifyChat;
					notifyChat.type = mmo::EChatType::Direct;
					notifyChat.senderName = gameSession->GetPlayer()->GetNickname();
					notifyChat.message = chat.message;

					if (auto targetSession = player->GetSession())
						targetSession->Send(&notifyChat, true);
					break;
				}
			}
		}
	}
}

void ObjectManager::HandleAllChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto sender = gameSession->GetPlayer();

	gen::mmo::NotifyChat notifyChat;
	notifyChat.type = mmo::EChatType::All;
	notifyChat.senderName = sender->GetNickname();
	notifyChat.message = chat.message;

	BroadcastAll(&notifyChat, sender->GetId());
}

void ObjectManager::BroadcastAll(Packet* packet, uint64 ignore)
{
	for (const auto& [_, object] : m_objects)
	{
		if (object->GetType() == mmo::EObjectType::PLAYER)
		{
			auto player = std::static_pointer_cast<Player>(object);
			if (player->GetId() != ignore)
			{
				if (auto session = player->GetSession())
					session->Send(packet);
			}
		}
	}
}
