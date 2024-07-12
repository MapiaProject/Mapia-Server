#include "pch.h"
#include "generated/mmo/ServerPacketHandler.gen.hpp"
#include "Session/GameSession.hpp"

#include "Object/Object.hpp"
#include "Storage/GameMap.hpp"

#include "Manager/Manager.hpp"
#include "Manager/ObjectManager.hpp"
#include "Manager/MapManager.hpp"

using namespace gen;

bool mmo::PacketHandler::EnterGameReqPacketHandler(Session* session, TSharedPtr<EnterGameReq> packet)
{
	GManager->Object()->Run(&ObjectManager::HandleEnterGame, session, packet);
	return false;
}

bool mmo::PacketHandler::EnterMapReqPacketHandler(Session* session, TSharedPtr<EnterMapReq> packet)
{
	GManager->Map()->Run(&MapManager::HandleEnter, session, packet);
	return false;
}

bool mmo::PacketHandler::MovePacketHandler(Session* session, TSharedPtr<Move> packet)
{
	auto gameSession = static_cast<GameSession*>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Run(&GameMap::HandleMove, session, packet);
	return false;
}

bool gen::mmo::PacketHandler::ChatPacketHandler(Session* session, TSharedPtr<Chat> packet)
{
	auto gameSession = static_cast<GameSession*>(session);
	switch (packet->type)
	{
	case gen::mmo::EChatType::Direct:
		GManager->Object()->Run(&ObjectManager::HandleDirectChat, session, packet);
		break;
	case gen::mmo::EChatType::Local:
		if (auto map = gameSession->GetPlayer()->GetMap())
			map->Run(&GameMap::HandleLocalChat, session, packet);
		break;
	case gen::mmo::EChatType::All:
		GManager->Object()->Run(&ObjectManager::HandleAllChat, session, packet);
		break;
	default:
		break;
	}
	return false;
}

bool gen::mmo::PacketHandler::AddDamageReqPacketHandler(Session* session, TSharedPtr<AddDamageReq> packet)
{
	auto gameSession = static_cast<GameSession*>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Run(&GameMap::HandleDamage, session, packet);
	return false;
}

bool gen::mmo::PacketHandler::HitStatusPacketHandler(Session* session, TSharedPtr<HitStatus> packet)
{
	auto gameSession = static_cast<GameSession*>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Run(&GameMap::HandleHitStatus, session, packet);
	return false;
}

bool gen::mmo::PacketHandler::SkillActivatePacketHandler(Session* session, TSharedPtr<SkillActivate> packet)
{
	auto gameSession = static_cast<GameSession*>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->Run(&GameMap::HandleSkillActivate, session, packet);
	return false;
}