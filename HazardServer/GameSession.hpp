#pragma once

#include <Network/Session.hpp>
#include <Room.hpp>

#include <generated/ServerPacketHandler.gen.hpp>

class GameSession : public Session
{
public:
	GameSession() = default;
	~GameSession() = default;
public:
	virtual void onConnected() override
	{
		Console::Log(LogServer, Log, L"Connected!");
	}
	virtual void onDisconnected() override
	{
		Console::Log(LogServer, Log, L"Disonnected!");
	}
	virtual void onReceive(std::span<char> buffer, int32 len) override
	{
		gen::PacketHandler::handlePacket(shared_from_this(), buffer);
	}
private:
	uint32 m_id;
	std::weak_ptr<class SessionManager> m_sessionManager;
};
