#include "pch.h"
#include "GameSession.hpp"
#include "Network/Server.hpp"

using namespace std;

int main()
{
	try {
		auto server = Server::Open<GameSession>();
		server->Run(Endpoint(IpAddress::Any, 9999));

		for (int i = 0; i < 4; ++i)
		{
			GEngine->GetThreadManager()->Launch([]()
			{
				GEngine->ExecuteIocpLogic();
			});
		}

		Console::Log("Server is running");

		GEngine->ExecuteIocpLogic();

		GEngine->GetThreadManager()->Join();
	}
	catch (exception& e) {
		Console::Log(e.what());
	}
}