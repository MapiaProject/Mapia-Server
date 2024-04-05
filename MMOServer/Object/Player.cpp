#include "pch.h"
#include "Player.hpp"
#include "GameMap.hpp"

Player::Player(uint64 id) : NetObject(id), m_position(Vector2DI::Zero())
{
}

void Player::SetSession(std::shared_ptr<GameSession> session)
{
	m_session = session;
}

void Player::EnterMap(std::shared_ptr<GameMap> gameMap)
{
	if (auto map = m_map.lock())
		LeaveMap();
	else
		m_map = gameMap;

	if (auto map = m_map.lock())
		gameMap->AddPlayer(std::static_pointer_cast<Player>(shared_from_this()));
}

void Player::LeaveMap()
{
	if (auto map = m_map.lock())
		map->RemovePlayer(std::static_pointer_cast<Player>(shared_from_this()));

	// TODO: broadcast leave info
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
