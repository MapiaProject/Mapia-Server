#include "pch.h"
#include "Monster.hpp"
#include "Storage/GameMap.hpp"
#include "Object/Player.hpp"
#include "Session/GameSession.hpp"

#include "Manager/DataManager.hpp"


Monster::Monster(uint64 id, mmo::EObjectType type, std::shared_ptr<class GameMap> map)
	: NetObject(id, type),
	m_map(map), m_enableAutomove(true), m_dir(0), m_target(), m_patrol(true), m_state(PATROL)
{
	SetPosition(Vector2DF::Zero());
	m_moveTime = GetTickCount64();
	m_nextMoveTime = GetTickCount64();
	m_attackTime = GetTickCount64();
	m_dest = 0;

	auto info = GManager->Data()->GetMonsterData(type);
	SetHp(info.hp);
	SetPower(info.power);
	SetAttackRange(info.attackRange);
}

void Monster::BeginPlay()
{
	NetObject::BeginPlay();
	if (m_enableAutomove)
	{
		NextDestination();
		m_state = PATROL;
	}
	else
	{
		m_state = IDLE;
	}
}
	
void Monster::Tick()
{
	NetObject::Tick();

	if (m_state == FAINT && m_endFaintTick >= GetTickCount64())
	{
		m_state = IDLE;
	}

	// attack
	if (auto target = m_target.lock(); target && m_state != FAINT)
	{
		if ((GetPosition() - target->GetPosition()).Length() > m_attackRange)
		{
			m_target.reset();
			if (m_enableAutomove)
				m_state = PATROL;
			else
				m_state = IDLE;
		}
		else if (GetTickCount64() >= m_attackTime)
		{
			Attack();
			m_attackTime = GetTickCount64() + m_attackTick;
		}
	}
	else if (m_enableAutomove)
		m_state = PATROL;
	else
		m_state = IDLE;

	// auto move
	if (m_enableAutomove && m_state == PATROL)
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
			m_moveTime = GetTickCount64() + m_moveTick;

			mmo::NotifyMove move;
			move.objectId = GetId();
			move.position = Converter::MakeVector(GetPosition());
			if (auto map = GetMap())
				map->Broadcast(&move);
		}
	}
}

void Monster::OnDestroy(const std::shared_ptr<NetObject>& hitter)
{
	NetObject::OnDestroy(hitter);
	if (hitter->GetType() == mmo::PLAYER)
	{
		auto player = std::static_pointer_cast<Player>(hitter);
		for (const auto& dropItem : GManager->Data()->GetDropsData(GetType()))
		{
			//player->AddItem(dropItem.id);
		}
	}

	if (auto map = GetMap())
	{
		map->Leave(shared_from_this());
	}
}

void Monster::OnDamaged(const std::shared_ptr<NetObject> attacker)
{
	if (attacker && attacker->GetType() == mmo::EObjectType::PLAYER)
		m_target = std::static_pointer_cast<Player>(attacker);
}

void Monster::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	if (!target)
		return;

	const auto& player = std::static_pointer_cast<Player>(target);
	player->TryDamage(shared_from_this());
	mmo::TakeAttack attack;
	attack.target = player->GetId();
	if (auto session = player->GetSession())
		session->Send(&attack);
}

void Monster::SetAutomove(bool enable)
{
	m_enableAutomove = enable;
}

std::shared_ptr<GameMap> Monster::GetMap() const
{
	return m_map.lock();
}

void Monster::SetAttackRange(float range)
{
	m_attackRange = range;
}

float Monster::GetAttackRange() const
{
	return m_attackRange;
}

void Monster::Faint(int32 power)
{
	TakeDamage(nullptr, power);

	m_state = FAINT;
	m_endFaintTick = GetTickCount64() + FAINT_TIME;
}

bool Monster::IsAutomove() const
{
	return m_enableAutomove;
}

uint64 Monster::GetAttackTick() const
{
	return m_attackTick;
}

uint64 Monster::GetMoveTick() const
{
	return m_moveTick;
}

void Monster::SetAttackTick(uint64 tick)
{
	m_attackTick = tick;
}

void Monster::SetMoveTick(uint64 tick)
{
	m_moveTick = tick;
}

void Monster::NextDestination()
{
	auto map = m_map.lock();
	if (!map)
		return;

	m_state = PATROL;

	auto [x, y] = GetPosition();
	m_dir = Random::Range(-1, 1);
	if (m_dir != 0)
	{
		for (; map->GetBlock(Vector2DI{
			static_cast<int32>(x + m_dir),
			static_cast<int32>(y)
			}) == Block::SpawnArea;
			x += m_dir
		);
	}

	if (x >= 0)
		m_dest = Random::Range<int32>(0, static_cast<int32>(x));
	else
		m_dest = Random::Range<int32>(static_cast<int32>(x), 0);
}

void Monster::Attack()
{
	if (auto target = m_target.lock())
	{
		m_state = ATTACK;

		ProcessAttack(target);
	}
	else if (m_enableAutomove)
		m_state = PATROL;
	else m_state = IDLE;
}
