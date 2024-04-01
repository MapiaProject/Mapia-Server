#include "pch.h"
#include "GameSession.hpp"

void GameSession::OnConnected(net::Endpoint)
{
	Console::Log(Category::MMOServer, Info, L"Connected!");
}

void GameSession::OnDisconnected(net::Endpoint)
{
	Console::Log(Category::MMOServer, Info, L"Disconnected!");
}

void GameSession::OnReceive(std::span<char> buffer, int32)
{
	gen::mmo::PacketHandler::handlePacket(shared_from_this(), buffer);
}

void GameSession::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}

std::shared_ptr<Player> GameSession::GetPlayer()
{
	return m_player;
}
