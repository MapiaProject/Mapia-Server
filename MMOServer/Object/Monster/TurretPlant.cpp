#include "pch.h"
#include "TurretPlant.hpp"
#include "Object/Player.hpp"
#include "Storage/GameMap.hpp"

TurretPlant::TurretPlant(uint64 id, std::shared_ptr<GameMap> map)
	: Monster(id, mmo::TurretPlant, map)
{
}

void TurretPlant::BeginPlay()
{
	Monster::BeginPlay();
	SetAutomove(false);
	m_tick = GetTickCount64();
}

void TurretPlant::Tick()
{
	Monster::Tick();
	if (m_projectile)
	{
		auto map = GetMap();
		if (!map)
			return;

		if (m_tick >= GetTickCount64())
		{
			m_tick = GetTickCount64() + UPDATE_PROJECTILE_TICK;
			
			mmo::NotifyMove move;
			move.objectId = GetId();
			move.position = Converter::MakeVector(m_projectile->GetPosition());
			map->Broadcast(&move);
		}

		if ((m_targetPosition - m_projectile->GetPosition()).Length() >= 0.2f)
		{
			auto dir = (m_targetPosition - GetPosition()).Normalize();
			m_position += dir * GetDeltatime();
		}
		else
		{
			if (auto target = m_target.lock(); target)
			{
				for (const auto&[_, player] : map->GetPlayers())
				{
					if ((player->GetPosition() - m_projectile->GetPosition()).Length() < 0.2f)
					{
						mmo::NotifyDamaged damage;
						damage.damageResult.damage = GetPower();
						damage.damageResult.objectId = target->GetId();
						map->Broadcast(&damage);
					}
				}
			}
			m_projectile = nullptr;
		}
	}
}

void TurretPlant::ProcessAttack(const std::shared_ptr<NetObject> target)
{
	if (auto map = GetMap(); map && !m_projectile)
	{
		m_target = std::static_pointer_cast<Player>(target);
		m_targetPosition = target->GetPosition();

		m_projectile = CreateObject(NetObject, mmo::Projectile);
		m_projectile->SetPosition(GetPosition());

		mmo::NotifySpawn spawn;
		mmo::ObjectInfo info;
		info.objectId = m_projectile->GetId();
		info.position = Converter::MakeVector(m_projectile->GetPosition());
		info.type = mmo::Projectile;
		spawn.objects.push_back(info);
		map->Broadcast(&spawn);
	}
}
