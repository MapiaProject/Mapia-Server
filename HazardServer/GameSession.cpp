#include "pch.h"
#include "GameSession.hpp"

void GameSession::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}
