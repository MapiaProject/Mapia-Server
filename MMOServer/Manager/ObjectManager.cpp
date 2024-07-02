#include "pch.h"
#include "ObjectManager.hpp"
#include "Session/GameSession.hpp"
#include "Object/Player.hpp"
#include "Manager.hpp"

#include "Database/DBConnectionPool.hpp"
#include "Database/Statement.hpp"

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
	res.success = gameSession->GetPlayer() == nullptr;
	if (res.success)
	{
		auto conn = GEngine->GetDBConnectionPool()->Pop();
		if (conn)
		{
			uint32 level = 0;
			auto stmt = conn->CreateStatement<1, 1>(TEXT("SELECT clevel FROM usercharacter WHERE nickname = ?"));
			stmt.SetParameter(0, req.name.c_str());
			stmt.Bind(0, reinterpret_cast<int32&>(level));
			if (!stmt.ExecuteQuery())
				Console::Error(Category::Database, TEXT("Invalid SQL syntax"));
			stmt.Next();
			if (level == 0)
			{
				level = 1;
				auto stmt = conn->CreateStatement<1, 0>(TEXT("INSERT INTO usercharacter VALUES(?, 1)"));
				stmt.SetParameter(0, req.name.c_str());
				if (!stmt.ExecuteQuery())
					Console::Error(Category::Database, TEXT("Already existing row"));
			}

			res.level = level;

			auto player = Create<Player>(level);
			player->SetNickname(nickname);
			player->SetSession(gameSession);
			player->BeginPlay();
			gameSession->SetPlayer(player);

			GEngine->GetDBConnectionPool()->Push(conn);
		}
		else
		{
		}
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
