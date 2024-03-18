#include "pch.h"
#include "Session/GameSession.hpp"

#include "generated/mmo/ServerPacketHandler.gen.hpp"

#include "Managers/Manager.hpp"
#include "Managers/RoomManager.hpp"
#include "Managers/DatabaseManager.hpp"

using namespace gen;

bool mmo::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
    GManager->GetRoom()->Launch(&RoomManager::HandleEnterGame, session);
    return false;
}

bool mmo::PacketHandler::RoomEventReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<RoomEventReq> packet)
{
    GManager->GetRoom()->Launch(&RoomManager::HandleRoomEvent, session, *packet);
    return false;
}