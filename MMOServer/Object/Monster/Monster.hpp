#pragma once
#include "Object/NetObject.hpp"

class Monster : public NetObject
{
public:
	Monster(uint64 id);

	virtual void Tick(float deltaTime) override;
};

