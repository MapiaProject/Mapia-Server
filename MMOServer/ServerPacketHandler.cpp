#include "pch.h"
#include "generated/mmo/ServerPacketHandler.gen.hpp"
#include "Session/GameSession.hpp"

#include "Object/Player.hpp"
#include "Object/GameMap.hpp"

#include "Manager/Manager.hpp"
#include "Manager/NetObjectManager.hpp"
#include "Manager/MapManager.hpp"

using namespace gen;

bool mmo::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
	GManager->NetObject()->Launch(&NetObjectManager::HandleEnterGame, session, *packet);
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
	return false;
}
