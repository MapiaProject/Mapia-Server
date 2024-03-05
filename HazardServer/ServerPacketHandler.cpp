#include "pch.h"
#include "generated/ServerPacketHandler.gen.hpp"

#include "GameSession.hpp"
#include "Managers/Manager.hpp"
#include "Managers/RoomManager.hpp"

bool gen::PacketHandler::LoginReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginReq> packet)
{
    return false;
}

bool gen::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
    GManager->GetRoom()->Launch(&RoomManager::HandleEnterGame, session);
    return false;
}

bool gen::PacketHandler::RoomEventReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<RoomEventReq> packet)
{
    GManager->GetRoom()->Launch(&RoomManager::HandleRoomEvent, session, *packet);
    return false;
}