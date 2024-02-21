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
		GRoom->Launch(1000, [] { Console::Log(LogServer, Debug, TEXT("1000")); });
		GRoom->Launch(2000, [] { Console::Log(LogServer, Debug, TEXT("2000")); });
		GRoom->Launch(3000, [] { Console::Log(LogServer, Debug, TEXT("3000")); });
	}
	virtual void onDisconnected() override
	{
		Console::Log(LogServer, Log, L"Disonnected!");
	}
	virtual void onReceive(std::span<char> buffer, int32 len) override
	{
		gen::PacketHandler::handlePacket(shared_from_this(), buffer);
	}
};
