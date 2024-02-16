#pragma once

#include <Network/Session.hpp>

class GameSession : public Session
{
public:
	virtual void onConnected() override
	{
		Console::Log("Connected!");
	}
	virtual void onDisconnected() override
	{
		Console::Log("Disonnected!");
	}
	virtual void onReceive(std::span<char> buffer, int32 len) override
	{
		Console::Log("RECV");
	}
};
