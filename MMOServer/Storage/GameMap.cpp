#include "pch.h"
#include "GameMap.hpp"
#include "Object/Player.hpp"
#include "Session/GameSession.hpp"
#include "Manager/MapManager.hpp"

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
	for (const auto& pair : m_objects)
	{
		const auto& object = pair.second;
		if (pair.first != ignore && object->GetType() == mmo::Player)
		{
			if (auto session = std::static_pointer_cast<Player>(object)->GetSession())
				session->SendBuffered(buffer);
		}
	}
}

void GameMap::Broadcast(Packet* packet, uint64 ignore)
{
	for (const auto& pair : m_objects)
	{
		const auto& object = pair.second;
		if (pair.first != ignore && object->GetType() == mmo::Player)
		{
			if (auto session = std::static_pointer_cast<Player>(object)->GetSession())
				session->Send(packet, true);
		}
	}
}

Vector<std::shared_ptr<Player>> GameMap::Players()
{
	Vector<std::shared_ptr<Player>> players;
	for (const auto& pair : m_objects)
	{
		if (pair.second->GetType() == mmo::Player)
			players.push_back(std::static_pointer_cast<Player>(pair.second));
	}
	return players;
}

Vector<std::shared_ptr<class Monster>> GameMap::Monsters()
{
	Vector<std::shared_ptr<Monster>> monsteres;
	for (const auto& pair : m_objects)
	{
		if (pair.second->GetType() == mmo::Monster)
			monsteres.push_back(std::static_pointer_cast<Monster>(pair.second));
	}
	return monsteres;
}

void GameMap::Enter(std::shared_ptr<class Player> player)
{
	m_objects.insert({ player->GetId(), player });
}

void GameMap::Leave(std::shared_ptr<class Player> player)
{
	m_objects.erase(player->GetId());
}

void GameMap::HandleMove(std::shared_ptr<Session> session, gen::mmo::Move move)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();

	gen::mmo::NotifyMove syncMove;
	auto prevPos = player->GetPosition();
	auto block = GetBlock(Point2DI(move.position.x, move.position.y));
	if (block != Block::Border)
		syncMove.position = move.position;
	else
		syncMove.position = Converter::MakeVector(prevPos);

	Broadcast(&syncMove);
}

void GameMap::HandleLocalChat(std::shared_ptr<Session> session, gen::mmo::Chat chat)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	auto sender = gameSession->GetPlayer();

	gen::mmo::NotifyChat notifyChat;
	notifyChat.senderName = sender->GetNickname();
	notifyChat.message = chat.message;

	Broadcast(&notifyChat, sender->GetId());
}

void GameMap::Update()
{
	Launch<100>(&GameMap::Update);

	static const auto spawnArea = GetBlocks(Block::SpawnArea);
	int count = 0;
	while (count + Monsters().size() < 10)
	{
		auto idx = action::Random::RandomRange<uint32>(0, spawnArea.size());
		auto spawn = spawnArea[idx];
		gen::mmo::SpawnMonster monster;
		count++;
	}

	// NetObject `Update` logic
	for (const auto& pair : m_objects)
	{
		auto player = pair.second;
		player->Update();
	}
}
