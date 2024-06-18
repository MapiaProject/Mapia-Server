#include "pch.h"
#include "Player.hpp"
#include "Storage/GameMap.hpp"

Player::Player() noexcept
{
	SetHp(10);
	if (auto map = GetMap())
		map->Leave(shared_from_this());
}

Player::Player(uint64 id) : NetObject(id, mmo::Player)
{
	SetPosition(Vector2DF::Zero());
}

void Player::BeginPlay()
{
	NetObject::BeginPlay();
}

void Player::Tick()
{
	NetObject::Tick();
}

void Player::OnDestroy()
{
	NetObject::OnDestroy();
	if (auto map = GetMap())
	{
		map->Leave(shared_from_this());
	}
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
		gameMap->Enter(shared_from_this());
}

void Player::LeaveMap()
{
	if (auto map = m_map.lock())
	{
		map->Launch(&GameMap::Leave, shared_from_this());
		m_map.reset();
	}
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

String Player::GetNickname() const
{
	return m_nickname;
}
