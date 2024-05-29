#include "pch.h"
#include "Monster.hpp"

Monster::Monster(uint64 id) : NetObject(id, mmo::Monster)
{
	SetPosition(Vector2DI::Zero());
}

void Monster::Update()
{
	Console::Log(Category::Temp, LogType::Debug, TEXT("Update Monster"));
}
