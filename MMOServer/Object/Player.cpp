#include "pch.h"
#include "Player.hpp"

Player::Player(uint64 id) : NetObject(id)
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

std::shared_ptr<GameSession> Player::GetSession()
{
	return m_session.lock();
}

std::shared_ptr<GameMap> Player::GetMap()
{
	return m_map.lock();
}
