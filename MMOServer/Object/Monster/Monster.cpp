#include "pch.h"
#include "Monster.hpp"
#include "Storage/GameMap.hpp"

Monster::Monster(uint64 id, std::shared_ptr<GameMap> map) : NetObject(id, mmo::Monster), m_map(map)
{
	SetPosition(Vector2DF::Zero());
	m_nextTime = GetTickCount64();
	m_dest = 0;
}

void Monster::BeginPlay()
{
	NextDestination();
}

void Monster::Tick(float deltaTime)
{
	if (GetTickCount64() > m_nextTime)
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
		else
		{
			m_nextTime = GetTickCount64() + Random::Range(250, 750);
			NextDestination();
		}
	}
}

void Monster::NextDestination()
{
	auto map = m_map.lock();
	if (!map)
		return;

	auto [x, y] = GetPosition();
	m_dir = Random::Range(-1, 1);
	if (m_dir != 0) for (; map->GetBlock(Vector2DI(x + m_dir, y - 1)) == Block::SpawnArea; x += m_dir);

	if (x >= 0)
		m_dest = Random::Range<int>(0, x);
	else
		m_dest = Random::Range<int>(x, 0);
}
