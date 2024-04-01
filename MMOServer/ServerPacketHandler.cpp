#include "pch.h"
#include "generated/mmo/ServerPacketHandler.gen.hpp"
#include "Session/GameSession.hpp"

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