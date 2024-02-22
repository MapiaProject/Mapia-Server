#include "pch.h"
#include "generated/ServerPacketHandler.gen.hpp"

#include "Managers/Manager.hpp"

bool gen::PacketHandler::LoginReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<LoginReq> packet)
{
    return false;
}

bool gen::PacketHandler::EnterGameReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterGameReq> packet)
{
    std::lock_guard lock(s_mtx);
    gen::EnterGameRes res;
    const auto rooms = GManager->GetRoomList();
    for (int i = 0; i < rooms.size(); ++i) {

    }
    return false;
}

bool gen::PacketHandler::EnterRoomReqPacketHandler(TSharedPtr<Session> session, TSharedPtr<EnterRoomReq> packet)
{
    return false;
}
