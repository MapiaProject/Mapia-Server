#include "pch.h"
#include "GameSession.hpp"
#include "Room.hpp"

void GameSession::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}

void GameSession::SetRoom(std::shared_ptr<Room> room)
{
	m_room = room;
}
