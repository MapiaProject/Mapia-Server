#include "pch.h"
#include "GameSession.hpp"
#include "Network/Server.hpp"

using namespace std;

int main()
{
	try {
		auto endpoint = Endpoint(IpAddress::Any, 9999);
		auto server = Server::Open<GameSession>();
		server->Run(endpoint);

		Console::Log(LogServer, Log, L"Server is running on " + action::ToUnicodeString(endpoint.toString()));

		GEngine->ExecuteIocpLogic(std::thread::hardware_concurrency(), true);
	}
	catch (exception& e) {
		Console::Log(LogServer, Error, action::ToUnicodeString(e.what()));
	}
}