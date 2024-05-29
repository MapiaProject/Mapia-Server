#include "pch.h"
#include "Monster.hpp"

Monster::Monster(uint64 id) : NetObject(id, mmo::Monster)
{
	SetPosition(Vector2DI::Zero());
}
