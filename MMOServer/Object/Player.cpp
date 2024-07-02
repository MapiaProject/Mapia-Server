#include "pch.h"
#include "Player.hpp"
#include "Storage/GameMap.hpp"
#include "Object.hpp"

#include "Manager/DataManager.hpp"

Player::Player(uint64 id, uint32 level) : NetObject(id, mmo::PLAYER), m_level(level)
{
	SetPosition(Vector2DF::Zero());
	m_airborne = GManager->Data()->GetSkillData(mmo::ESkillType::Airborne);

	const auto& info = GManager->Data()->GetStatData(m_level);
	SetHp(info.health);
	SetPower(info.power);
}

void Player::BeginPlay()
{
	NetObject::BeginPlay();
	m_lastPosX = m_position.x;
	m_isLookAtRight = true;
}

void Player::Tick()
{
	NetObject::Tick();
	auto&& diff = m_position.x - m_lastPosX;
	if (diff > 0)
	{
		m_isLookAtRight = true;
	}
	else if (diff < 0)
	{
		m_isLookAtRight = false;
	}
	m_lastPosX = m_position.x;
}

void Player::OnDestroy(const std::shared_ptr<NetObject>& object)
{
	NetObject::OnDestroy(object);
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

void Player::ObtainItem(Vector<ItemData> items)
{
	for (const auto& item : items)
	{
		m_inventory.items[item.type]++;
	}
}

void Player::Airborne() const
{
	auto map = GetMap();
	if (!map)
		return;

	for (const auto& [_, monster] : map->GetMonsters())
	{
		auto diff = monster->GetPosition() - GetPosition();
		if (!m_isLookAtRight)
			diff.x = -diff.x;
		if (diff.x <= m_airborne.range.x && Math::Abs(diff.y) <= m_airborne.range.y)
		{
			monster->Faint(m_airborne.damage);
		}
	}
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
