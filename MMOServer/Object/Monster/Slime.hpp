#pragma once
#include "Monster.hpp"

class Slime : public Monster
{
public:
	virtual void Tick(float deltaTime) override;
};

