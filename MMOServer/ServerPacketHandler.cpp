#include "pch.h"
#include "generated/mmo/ServerPacketHandler.gen.hpp"
#include "Session/GameSession.hpp"

#include "Object/Player.hpp"
#include "Storage/GameMap.hpp"

#include "Manager/Manager.hpp"
#include "Manager/NetObjectManager.hpp"
#include "Manager/MapManager.hpp"

using namespace gen;

bool mmo::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
	GManager->Object()->Launch(&NetObjectManager::HandleEnterGame, session, *packet);
	return false;
}

bool mmo::PacketHandler::EnterMapReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterMapReq> packet)
{
	GManager->Map()->Launch(&MapManager::HandleEnter, session, *packet);
	return false;
}

bool mmo::PacketHandler::MovePacketHandler(TSharedPtr<Session> session, TSharedPtr<Move> packet)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Launch(&GameMap::HandleMove, session, *packet);
	return false;
}

bool gen::mmo::PacketHandler::ChatPacketHandler(TSharedPtr<Session> session, TSharedPtr<Chat> packet)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	switch (packet->type)
	{
	case gen::mmo::EChatType::Direct:
		GManager->Object()->Launch(&NetObjectManager::HandleDirectChat, session, *packet);
		break;
	case gen::mmo::EChatType::Local:
		if (auto map = gameSession->GetPlayer()->GetMap())
			map->Launch(&GameMap::HandleLocalChat, session, *packet);
		break;
	case gen::mmo::EChatType::All:
		GManager->Object()->Launch(&NetObjectManager::HandleAllChat, session, *packet);
		break;
	default:
		break;
	}
	return false;
}

bool gen::mmo::PacketHandler::AddDamageReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<AddDamageReq> packet)
{
	auto gameSession = std::static_pointer_cast<GameSession>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Launch(&GameMap::HandleDamage, session, *packet);
	return false;
}

bool gen::mmo::PacketHandler::HitStatusPacketHandler(TSharedPtr<Session> session, TSharedPtr<HitStatus> packet)
{

	return false;
}
