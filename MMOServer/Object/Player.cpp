#include "pch.h"
#include "Player.hpp"
#include "Storage/GameMap.hpp"

Player::Player() noexcept
{
	SetHp(10);
	SetPower(2);
	if (auto map = GetMap())
		map->Leave(shared_from_this());
}

Player::Player(uint64 id) : NetObject(id, mmo::PLAYER)
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
	Console::Debug(Category::Temp, std::to_wstring(GetPosition().x) + TEXT(", ") + std::to_wstring(GetPosition().y));
}

void Player::OnDestroy()
{
	NetObject::OnDestroy();
	if (auto map = GetMap())
	{
		map->Leave(shared_from_this());
	}
}

void Player::OnDamaged(const std::shared_ptr<NetObject> hitter)
{
	m_hitter = hitter;
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
		gameMap->Enter(SharedThis());
}

void Player::LeaveMap()
{
	if (auto map = m_map.lock())
	{
		map->Launch(&GameMap::Leave, shared_from_this());
		m_map.reset();
	}
}

void Player::TryDamage(const std::shared_ptr<NetObject> hitter)
{
	OnDamaged(hitter);
}

std::shared_ptr<Player> Player::SharedThis()
{
	return std::static_pointer_cast<Player>(shared_from_this());
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

std::shared_ptr<NetObject> Player::GetHitter()
{
	return m_hitter.lock();
}
