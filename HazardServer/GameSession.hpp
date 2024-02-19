#pragma once

#include <Network/Session.hpp>

class GameSession : public Session
{
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
		
	}
};
