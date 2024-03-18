#include "pch.h"
#include "GameSession.hpp"
#include "Room/Room.hpp"

void GameSession::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}

void GameSession::SetRoom(std::shared_ptr<Room> room)
{
	m_room = room;
}

void GameSession::OnConnected(net::Endpoint)
{
	Console::Log(LogMMOServer, Log, L"Connected!");
}

void GameSession::OnDisconnected(net::Endpoint)
{
	Console::Log(LogMMOServer, Log, L"Disconnected!");
}

void GameSession::OnReceive(std::span<char> buffer, int32)
{
	gen::mmo::PacketHandler::handlePacket(shared_from_this(), buffer);
}