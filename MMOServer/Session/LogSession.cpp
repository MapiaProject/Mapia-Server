#include "pch.h"
#include "LogSession.hpp"

#include "generated/logs/Protocol.gen.hpp"

void LogSession::OnConnected(net::Endpoint ep)
{
	gen::logs::SystemLog sysLog;
	sysLog.category = gen::logs::START;
	sysLog.serverName = TEXT("MMO Server");
	Send(&sysLog);
}

void LogSession::OnDisconnected(net::Endpoint)
{

}

void LogSession::OnReceive(std::span<char>, int32)
{

}
