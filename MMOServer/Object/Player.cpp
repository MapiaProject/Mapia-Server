#include "pch.h"
#include "Player.hpp"
#include "Storage/GameMap.hpp"

Player::Player()
{
	m_position = Vector2DI(-1, -1);
	if (auto map = GetMap())
		map->Leave(std::static_pointer_cast<Player>(shared_from_this()));
}

Player::Player(uint64 id) : NetObject(id, mmo::Player), m_position(Vector2DI::Zero())
{
}

void Player::Update()
{
	Console::Log(Category::Temp, LogType::Info, std::format(TEXT("Update at {}"), GetId()));
}

void Player::SetSession(std::shared_ptr<GameSession> session)
{
	m_session = session;
}

void Player::EnterMap(std::shared_ptr<GameMap> gameMap)
{
	if (auto map = m_map.lock())
		LeaveMap();
	
	m_map = gameMap;
	if (auto map = m_map.lock())
		gameMap->Enter(std::static_pointer_cast<Player>(shared_from_this()));
}

void Player::LeaveMap()
{
	gen::mmo::NotifyLeaveMap leave;
	leave.objectId = GetId();

	auto map = m_map.lock();
	if (map)
	{
		map->Broadcast(&leave);
		map->Leave(std::static_pointer_cast<Player>(shared_from_this()));
	}
}

void Player::SetPosition(Vector2DI position)
{
	m_position = position;
}

void Player::SetNickname(StringView nickname)
{
	m_nickname = nickname;
}

std::shared_ptr<GameSession> Player::GetSession()
{
	return m_session.lock();
}

std::shared_ptr<GameMap> Player::GetMap() const
{
	return m_map.lock();
}

Vector2DI Player::GetPosition() const
{
	return m_position;
}

String Player::GetNickname() const
{
	return m_nickname;
}
