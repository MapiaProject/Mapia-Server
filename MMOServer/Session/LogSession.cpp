#include "pch.h"
#include "LogSession.hpp"
#include "Thread/ThreadManager.hpp"
#include "generated/logs/Protocol.gen.hpp"

void LogSession::OnConnected(net::Endpoint)
{
	gen::logs::SystemLog sysLog;
	sysLog.severity = gen::logs::ESeverity::INFO;
	sysLog.serverName = TEXT("MMO Server");
	sysLog.message = TEXT("Server started");
	Send(&sysLog);
}

void LogSession::OnDisconnected(net::Endpoint)
{
}

void LogSession::OnReceive(std::span<char>, int32)
{

}
void LogSession::OnFail(Failure)
{

}
