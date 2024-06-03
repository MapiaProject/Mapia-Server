#pragma once
#include "NetObject.hpp"

class Monster : public NetObject
{
public:
	Monster(uint64 id);

	void Tick(float deltaTime) override;
};

