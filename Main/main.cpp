#include "pch.h"
#include "Session/GameSession.hpp"
#include "Session/LogSession.hpp"
#include "Network/Server.hpp"
#include "Network/Client.hpp"
#include "MMOServer.hpp"

using namespace std;

int main()
{
	auto logEndpoint = Endpoint(net::IpAddress::Loopback, 1225);
	auto serverEndpoint = Endpoint(IpAddress::Loopback, 1004);
	try {
		auto server = Server::Open<GameSession>();
		auto client = Client::Open<LogSession>();
		server->Run(serverEndpoint);
		client->Run(logEndpoint);

		Console::Log(LogMMOServer, Log, TEXT("MMO Server is running on ") + action::ToUnicodeString(serverEndpoint.toString()));

		GEngine->ExecuteIocpLogic(thread::hardware_concurrency(), true);
	}
	catch (exception& e) {
		Console::Log(LogMMOServer, Error, action::ToUnicodeString(e.what()));
	}
}