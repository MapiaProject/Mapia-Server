#pragma once
#include "Object/NetObject.hpp"

class Projectile : public NetObject
{
	USE_POOL(Projectile)
public:
	Projectile(uint64 id, Vector2DF targetPosition);
protected:
	void BeginPlay() override;
	void Tick() override;
private:
	Vector2DF m_targetPos;
};

