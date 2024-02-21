#include "pch.h"
#include "Room.hpp"

std::shared_ptr<Room> GRoom = std::make_shared<Room>();

void Room::Enter()
{
	Console::Log(LogServer, Debug, TEXT("Enter"));
}

void Room::Leave()
{
	Console::Log(LogServer, Debug, TEXT("Leave"));
}

void Room::Behaviour()
{
	Console::Log(LogServer, Debug, TEXT("BEHAVIOUR"));
}
