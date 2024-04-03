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

void Player::SetMap(std::shared_ptr<GameMap> map)
{
	m_map = map;
	m_map.lock()->AddPlayer(std::static_pointer_cast<Player>(shared_from_this()));
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
