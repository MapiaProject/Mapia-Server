#pragma once
#include <Network/Session.hpp>

class LogSession : public Session
{
public:
	virtual void OnConnected(net::Endpoint) override;
	virtual void OnDisconnected(net::Endpoint) override;
	virtual void OnReceive(std::span<char>, int32) override;
};

