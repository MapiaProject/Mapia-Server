#include "pch.h"
#include "Monster.hpp"
#include "Storage/GameMap.hpp"

Monster::Monster(uint64 id, std::shared_ptr<GameMap> map)
	: NetObject(id, mmo::Monster),
	m_map(map), m_enableAutomove(true), m_dir(0), m_target(), m_patrol(true)
{
	SetPosition(Vector2DF::Zero());
	m_moveTime = GetTickCount64();
	m_nextMoveTime = GetTickCount64();
	m_dest = 0;
}

void Monster::BeginPlay()
{
	NetObject::BeginPlay();
	if (m_enableAutomove)
		NextDestination();
}

void Monster::Tick()
{
	NetObject::Tick();

	if (m_enableAutomove)
	{
		if (auto target = m_target.lock())
		{
			m_patrol = false;
			m_dest = static_cast<int32>(target->GetPosition().x);
			m_dir = (GetPosition().x - m_dest) ? -1 : 1;
		}
		else m_patrol = true;

		if (GetTickCount64() >= m_moveTime)
		{
			auto position = GetPosition();
			if (m_dir > 0 && position.x < m_dest)
			{
				position.x++;
				SetPosition(position);
			}
			else if (m_dir < 0 && position.x > m_dest)
			{
				position.x--;
				SetPosition(position);
			}
			else if (m_patrol)
			{
				m_nextMoveTime = GetTickCount64() + Random::Range(250, 750);
				NextDestination();
			}
			m_moveTime = GetTickCount64() + MoveTick;

			mmo::NotifyMove move;
			move.objectId = GetId();
			move.position = Converter::MakeVector(GetPosition());
			if (auto map = GetMap())
				map->Broadcast(&move);
		}
	}
}

void Monster::OnDestroy()
{
	NetObject::OnDestroy();
	if (auto map = GetMap())
	{
		map->Leave(shared_from_this());
	}
}

void Monster::OnDamaged(const std::shared_ptr<NetObject> attacker)
{
	m_target = attacker;
}

void Monster::EnableAutomove(bool enable)
{
	m_enableAutomove = enable;
}

std::shared_ptr<GameMap> Monster::GetMap() const
{
	return m_map.lock();
}

bool Monster::GetEnabledAutomove()
{
	return m_enableAutomove;
}

void Monster::NextDestination()
{
	auto map = m_map.lock();
	if (!map)
		return;

	auto [x, y] = GetPosition();
	m_dir = Random::Range(-1, 1);
	if (m_dir != 0)
		for (; map->GetBlock(Vector2DI(x + m_dir, y)) == Block::SpawnArea; x += m_dir);

	if (x >= 0)
		m_dest = Random::Range<int>(0, x);
	else
		m_dest = Random::Range<int>(x, 0);
}
