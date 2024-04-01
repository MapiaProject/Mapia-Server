#include "pch.h"
#include "Player.hpp"

Player::Player(uint64 id) : NetObject(id), m_position(Vector2DI::Zero())
{
}

void Player::SetSession(std::shared_ptr<GameSession> session)
{
	m_session = session;
}

void Player::SetMap(std::shared_ptr<GameMap> map)
{
	m_map = map;
}

void Player::SetPosition(Vector2DI position)
{
	m_position = position;
}

std::shared_ptr<GameSession> Player::GetSession()
{
	return m_session.lock();
}

std::shared_ptr<GameMap> Player::GetMap()
{
	return m_map.lock();
}

Vector2DI Player::GetPosition() const
{
	return m_position;
}
