#include "pch.h"
#include "GameSession.hpp"
#include "Object/Player.hpp"
#include "Object/GameMap.hpp"

void GameSession::OnConnected(net::Endpoint)
{
	Console::Log(Category::MMOServer, Info, L"Connected!");
}

void GameSession::OnDisconnected(net::Endpoint)
{
	if (auto map = GetPlayer()->GetMap())
		map->Launch(&GameMap::Leave, GetPlayer());
	
	Console::Log(Category::MMOServer, Info, L"Disconnected!");
}

void GameSession::OnReceive(std::span<char> buffer, int32)
{
    uint16 id = 0;
    memcpy(&id, buffer.data(), sizeof(uint16));
    if (Packet::IsRpcId(id))
    {   
        RpcTarget target;
        memcpy(&target, buffer.data() + sizeof(uint16), sizeof(uint16));

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
