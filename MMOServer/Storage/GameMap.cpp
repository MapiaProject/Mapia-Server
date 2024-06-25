#include "pch.h"
#include "GameMap.hpp"

#include "Object/Object.hpp"

#include "Session/GameSession.hpp"
#include "Manager/MapManager.hpp"

#include "Manager/NetObjectManager.hpp"

GameMap::GameMap(StringView path) : MapData(path)
{
}

GameMap::~GameMap()
{	
}

void GameMap::Broadcast(std::span<char> buffer, uint64 ignore)
{
	for (const auto&[id, player] : m_players)
	{
		if (id == ignore) continue;
		if (auto session = player->GetSession())
			session->SendAtomic(buffer);
	}
}

void GameMap::Broadcast(Packet* packet, uint64 ignore)
{
	for (const auto&[id, player] : m_players)
	{
		if (id == ignore) continue;
		if (auto session = player->GetSession())
			session->Send(packet, true);
	}
}

void GameMap::Enter(std::shared_ptr<NetObject> object)
{
	switch (object->GetType())
	{
	case mmo::EObjectType::Player:
		m_players.insert({
			object->GetId(),
			std::static_pointer_cast<Player>(object)
		});
		break;
	default:
		m_monsters.insert({
			object->GetId(),
			std::static_pointer_cast<Monster>(object)
		});
		break;
	}
}

void GameMap::Leave(std::shared_ptr<NetObject> object)
{
	mmo::NotifyLeaveMap leaveMap;
	leaveMap.objectId = object->GetId();
	switch (object->GetType())
	{
	case mmo::EObjectType::Player:
		m_players.erase(object->GetId());
		break;
	default:
		m_monsters.erase(object->GetId());
		break;
	}
	Broadcast(&leaveMap);
}

void GameMap::SpawnMonster()
{
	auto spawnMonster = GetSpawnMonster();
	if (!spawnMonster.has_value())
		return;

	Launch<SpawnTick>(&GameMap::SpawnMonster);

	const auto spawnArea = GetBlocks(Block::SpawnArea);
	auto count = m_monsters.size();
	if (spawnArea.size() > 0 && count < 10)
	{
		Vector<mmo::ObjectInfo> infos;
		for (int i = 0; i < 10 - count; ++i)
		{
			auto idx = Random::Range<uint32>(0, spawnArea.size() - 1);
			Vector2DI spawnPosition = spawnArea[idx];

			std::shared_ptr<Monster> monster = nullptr;
			switch (spawnMonster.value())
			{
			case mmo::Slime:
				monster = GManager->Object()->Create<Slime>(SharedThis());
				break;
			case mmo::TurretPlant:
				monster = GManager->Object()->Create<TurretPlant>(SharedThis());
				break;
			case mmo::GeminiRobot:
				monster = GManager->Object()->Create<GeminiRobot>(SharedThis());
				break;
			default:
				break;
			}
			if (!monster)
				return;

			monster->SetPosition(Vector2DF(spawnPosition.x, spawnPosition.y));
			monster->BeginPlay();

			m_monsters[monster->GetId()] = monster;

			mmo::ObjectInfo info;
			info.objectId = monster->GetId();
			info.position = Converter::MakeVector(spawnPosition);
			info.type = spawnMonster.value();
			infos.push_back(info);
		}
		mmo::NotifySpawn spawn;
		spawn.objects = infos;
		Broadcast(&spawn);
	}
}

std::shared_ptr<GameMap> GameMap::SharedThis()
{
	return std::static_pointer_cast<GameMap>(shared_from_this());
}

HashMap<uint64, std::shared_ptr<class Player>> GameMap::GetPlayers() const
{
	return m_players;
}

HashMap<uint64, std::shared_ptr<class Monster>> GameMap::GetMonsters() const
{
	return m_monsters;
}

void GameMap::HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();

	gen::mmo::NotifyMove syncMove;
	syncMove.objectId = player->GetId();
	auto prevPos = player->GetPosition();
	auto block = GetBlock(Vector2DI(std::round(move.position.x), std::round(move.position.y)));
	if (!block.has_value())
	{
		syncMove.position = Converter::MakeVector(prevPos);
		Broadcast(&syncMove);
	}
	else
	{
		switch (block.value())
		{
		case Block::Portal:
			Console::Debug(Category::Temp, TEXT("PORTAL"));
			break;
		case Block::Border:
			syncMove.position = Converter::MakeVector(prevPos);
			player->SetPosition(Converter::MakeVector<float>(syncMove.position));
			Broadcast(&syncMove);
			break;
		default:
			syncMove.position = move.position;
			player->SetPosition(Converter::MakeVector<float>(syncMove.position));
			Broadcast(&syncMove);
			break;
		}
	}
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
	const auto& object = GManager->Object()->GetObjectById(damage.damageInfo.objectId);
	if (object)
	{
		mmo::NotifyDamaged notify;
		object->TakeDamage(object, damage.damageInfo.damage);
		notify.damageResult.objectId = object->GetId();
		notify.damageResult.damage = object->GetHp();

		Broadcast(&notify);
	}
}

void GameMap::HandleHitStatus(std::shared_ptr<Session> session, gen::mmo::HitStatus hit)
{
	const auto& gameSession = std::static_pointer_cast<GameSession>(session);
	const auto& player = gameSession->GetPlayer();
	const auto& hitter = player->GetHitter();

	if (!player || !hitter)
		return;

	switch (hit.state)
	{
	case mmo::EPlayerState::Parrying:
		break;
	default:
		player->TakeDamage(nullptr, player->GetHitter()->GetPower()); // To reset player's hitter
		break;
	}
}

void GameMap::BeginPlay()
{
	if (auto spawnMonster = GetSpawnMonster(); spawnMonster.has_value())
		SpawnMonster();
}

void GameMap::Tick()
{
	Launch<GameTick>(&GameMap::Tick);

	// Execute NetObject's `Update` logic
	for (const auto&[_, object] : m_players)
	{
		object->Tick();
	}
	for (const auto& [_, object] : m_monsters)
	{
		object->Tick();
	}
}
