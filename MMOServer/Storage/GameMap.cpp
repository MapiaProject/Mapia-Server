#include "pch.h"
#include "GameMap.hpp"

#include "Object/Object.hpp"

#include "Session/GameSession.hpp"
#include "Manager/MapManager.hpp"

#include "Manager/NetObjectManager.hpp"

GameMap::GameMap()
{
}

GameMap::GameMap(StringView path) : MapData(path)
{
}

GameMap::~GameMap()
{
}

void GameMap::Broadcast(std::span<char> buffer, uint64 ignore)
{
	for (const auto&[id, object] : m_objects)
	{
		if (id != ignore && object->GetType() == mmo::Player)
		{
			if (auto session = std::static_pointer_cast<Player>(object)->GetSession())
				session->SendAtomic(buffer);
		}
	}
}

void GameMap::Broadcast(Packet* packet, uint64 ignore)
{
	for (const auto&[id, object] : m_objects)
	{
		if (id != ignore && object->GetType() == mmo::Player)
		{
			if (auto session = std::static_pointer_cast<Player>(object)->GetSession())
				session->Send(packet, true);
		}
	}
}

Vector<std::shared_ptr<Player>> GameMap::Players()
{
	Vector<std::shared_ptr<Player>> players;
	for (const auto&[_, object] : m_objects)
	{
		if (object->GetType() == mmo::Player)
			players.push_back(std::static_pointer_cast<Player>(object));
	}
	return players;
}

Vector<std::shared_ptr<class Monster>> GameMap::Monsters()
{
	Vector<std::shared_ptr<Monster>> monsteres;
	for (const auto&[_, object] : m_objects)
	{
		if (object->GetType() == mmo::Monster)
			monsteres.push_back(std::static_pointer_cast<Monster>(object));
	}
	return monsteres;
}

void GameMap::Enter(std::shared_ptr<Player> player)
{
	m_objects.insert({ player->GetId(), player });
}

void GameMap::Leave(std::shared_ptr<Player> player)
{
	mmo::NotifyLeaveMap leaveMap;
	leaveMap.objectId = player->GetId();
	m_objects.erase(player->GetId());
	Broadcast(&leaveMap);
}

void GameMap::SpawnMonster()
{
	const auto spawnArea = GetBlocks(Block::SpawnArea);
	auto count = Monsters().size();
	if (spawnArea.size() > 0 && count < 10)
	{
		Vector<mmo::ObjectInfo> infos;
		for (int i = 0; i < 10 - count; ++i)
		{
			auto idx = Random::Range<uint32>(0, spawnArea.size() - 1);
			Vector2DI spawnPosition = spawnArea[idx];

			auto monster = GManager->Object()->Create<Monster>(std::static_pointer_cast<GameMap>(shared_from_this()));
			monster->SetPosition(Vector2DF(spawnPosition.x, spawnPosition.y));
			monster->BeginPlay();

			m_objects[monster->GetId()] = monster;

			mmo::ObjectInfo info;
			info.position = Converter::MakeVector(spawnPosition);
			info.objectId = monster->GetId();
			infos.push_back(info);
		}
		mmo::SpawnMonster spawn;
		spawn.monsterInfos = infos;
		Broadcast(&spawn);
	}
}

void GameMap::HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();

	gen::mmo::NotifyMove syncMove;
	syncMove.objectId = player->GetId();
	auto prevPos = player->GetPosition();
	auto block = GetBlock(Vector2DI(move.position.x, move.position.y));
	if (!block.has_value())
	{
		syncMove.position = Converter::MakeVector(prevPos);
	}
	else
	{
		if (block != Block::Border)
			syncMove.position = move.position;
		else
			syncMove.position = Converter::MakeVector(prevPos);
		player->SetPosition(Converter::MakeVector<float>(syncMove.position));
	}
	Broadcast(&syncMove);
}

void GameMap::HandleLocalChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto sender = gameSession->GetPlayer();

	gen::mmo::NotifyChat notifyChat;
	notifyChat.type = mmo::EChatType::Local;
	notifyChat.senderName = sender->GetNickname();
	notifyChat.message = chat.message;

	Broadcast(&notifyChat, sender->GetId());
}

void GameMap::HandleDamage(std::shared_ptr<Session> session, mmo::AddDamageReq damage)
{
	if (const auto& object = m_objects[damage.damageInfo.objectId])
	{
		object->TakeDamage(damage.damageInfo.damage);
		mmo::NotifyDamaged notify;
		notify.damageResult.objectId = object->GetId();
		notify.damageResult.damage = object->GetHp();

		Broadcast(&notify);
	}
}

void GameMap::Tick()
{
	Launch<GameTick>(&GameMap::Tick);

	Launch(&GameMap::SpawnMonster);

	// NetObject `Update` logic
	for (const auto&[_, object] : m_objects)
	{
		object->Tick((GetTickCount64() - m_lastTick)/1000.f);
	}
	m_lastTick = GetTickCount64();
}
