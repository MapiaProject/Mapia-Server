#include "pch.h"
#include "GameSession.hpp"
#include "Object/Player.hpp"
#include "Storage/GameMap.hpp"

void GameSession::OnConnected(net::Endpoint)
{
	Console::Log(Category::MMOServer, Info, L"Connected!");
}

void GameSession::OnDisconnected(net::Endpoint)
{
    m_player->LeaveMap();
	Console::Log(Category::MMOServer, Info, L"Disconnected!");
}

void GameSession::OnReceive(std::span<char> buffer, int32 len)
{
    if (len < 3)
        return;

    uint16 id = *reinterpret_cast<uint16*>(buffer.data());
    if (Packet::IsRpcId(id))
    {   
        RpcTarget target = *reinterpret_cast<RpcTarget*>(buffer.data() + sizeof(uint16));
        switch (target)
        {
        case RpcTarget::All:
            if (auto map = m_player->GetMap())
                map->Broadcast(buffer);
            break;
        case RpcTarget::Other:
            if (auto map = m_player->GetMap())
                map->Broadcast(buffer, m_player->GetId());
            break;
        default:
            break;
        }
    }
    else
    {
        gen::mmo::PacketHandler::HandlePacket(shared_from_this(), id, buffer);
    }
}

void GameSession::SetPlayer(std::shared_ptr<Player> player)
{
	m_player = player;
}

std::shared_ptr<Player> GameSession::GetPlayer()
{
	return m_player;
}
