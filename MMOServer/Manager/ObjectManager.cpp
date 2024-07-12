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
	m_lastId = 0;
	Console::Log(Category::MMOServer, TEXT("'ObjectManager' initialized"));
}

void ObjectManager::RemoveObject(uint64 id)
{
	if (auto& object = m_objects[id])
		object = nullptr;
}

std::shared_ptr<GameObject> ObjectManager::GetObjectById(uint64 id)
{
	return m_objects[id];
}

void ObjectManager::HandleEnterGame(Session* session, std::shared_ptr<gen::mmo::EnterGameReq> req)
{
		if (!session) return;

	auto gameSession = static_cast<GameSession*>(session);
	const auto& nickname = req->name;

	// send enter game success or failure
	auto success = gameSession->GetPlayer() == nullptr;
	if (success)
	{
		auto pstmt = GDatabase->CallProcedure("SP_GetUserByName", ToAnsiString(req->name));
		pstmt->AsyncQuery([=, request=*req](std::shared_ptr<sql::ResultSet> rs) {
			rs->next();

			gen::mmo::EnterGameRes res;
			res.success = success;

			uint32 level = rs->getUInt(1);
			uint32 exp = rs->getUInt(2);
			if (level == 0)
			{
				level = 1;
				auto pstmt = GDatabase->CallProcedure("SP_CreateUser", ToAnsiString(request.name));
				pstmt->AsyncExecute();
			}
			res.level = level;
			res.exp = exp;

			auto player = Create<Player>(level, exp);
			player->SetNickname(nickname);
			player->SetSession(gameSession);
			player->BeginPlay();
			gameSession->SetPlayer(player);

			gameSession->Send(&res);
		});
	}
	else
	{
		mmo::EnterGameRes res;
		res.success = false;
		gameSession->Send(&res);
	}
}

void ObjectManager::HandleDirectChat(Session* session, std::shared_ptr<gen::mmo::Chat> chat)
{
	if (!session) return;

	auto gameSession = static_cast<GameSession*>(session);
	for (const auto& [_, object] : m_objects)
	{
		if (object->GetType() == mmo::EObjectType::PLAYER)
		{
			if (auto player = std::static_pointer_cast<Player>(object))
			{
				if (player->GetNickname() == chat->targetName)
				{
					gen::mmo::NotifyChat notifyChat;
					notifyChat.type = mmo::EChatType::Direct;
					notifyChat.senderName = gameSession->GetPlayer()->GetNickname();
					notifyChat.message = chat->message;

					if (auto targetSession = player->GetSession())
						targetSession->Send(&notifyChat);
					break;
				}
			}
		}
	}
}

void ObjectManager::HandleAllChat(Session* session, std::shared_ptr<gen::mmo::Chat> chat)
{
	if (!session) return;

	auto gameSession = static_cast<GameSession*>(session);
	auto sender = gameSession->GetPlayer();

	gen::mmo::NotifyChat notifyChat;
	notifyChat.type = mmo::EChatType::All;
	notifyChat.senderName = sender->GetNickname();
	notifyChat.message = chat->message;

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
