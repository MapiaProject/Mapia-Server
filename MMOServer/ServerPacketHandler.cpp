#include "pch.h"
#include "generated/mmo/ServerPacketHandler.gen.hpp"
#include "Session/GameSession.hpp"

#include "Manager/Manager.hpp"
#include "Manager/NetObjectManager.hpp"

using namespace gen;

bool mmo::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
	GManager->NetObject()->Launch(&NetObjectManager::HandleEnterGameReq, session, *packet);
	return false;
}