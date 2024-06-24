#include "pch.h"
#include "Projectile.hpp"
#include "Storage/GameMap.hpp"

Projectile::Projectile(uint64 id, Vector2DF targetPosition)
	: NetObject(id, mmo::EObjectType::Projectile), m_targetPos(targetPosition)
{
}

void Projectile::BeginPlay()
{
}

void Projectile::Tick()
{
	
}
