#include "pch.h"
#include "GameSession.hpp"
#include "Network/Server.hpp"
#include "MMOServer.hpp"

using namespace std;

int main()
{
	try {
		auto endpoint = Endpoint(IpAddress::Any, 1225);
		auto server = Server::Open<GameSession>();
		server->Run(endpoint);

		Console::Log(LogMMOServer, Log, TEXT("MMO Server is running on ") + action::ToUnicodeString(endpoint.toString()));

		GEngine->ExecuteIocpLogic(std::thread::hardware_concurrency(), true);
	}
	catch (exception& e) {
		Console::Log(LogMMOServer, Error, action::ToUnicodeString(e.what()));
	}
}