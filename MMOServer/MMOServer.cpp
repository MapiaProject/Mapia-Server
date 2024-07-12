#include "pch.h"
#include "MMOServer.hpp"
#include "Manager/Manager.hpp"
#include "Session/GameSession.hpp"
#include "Session/LogSession.hpp"
#include "Network/Server.hpp"
#include "Network/Client.hpp"

Engine* GEngine;
Database* GDatabase;
Manager* GManager;

MMOServer::MMOServer()
{
	GEngine = new Engine;
	GDatabase = new Database;
	GManager = new Manager;
}

MMOServer::~MMOServer()
{
	delete GEngine;
	delete GDatabase;
	delete GManager;
}

void MMOServer::Run()
{
	GEngine->Initialize();
	GDatabase->Initialize();
	GManager->Initialize();

	auto logEndpoint = Endpoint(net::IpAddress::Loopback, 1225);
	auto serverEndpoint = Endpoint(IpAddress::Loopback, 1004);
	auto server = Server::Open<GameSession>();
	auto client = Client::Open<LogSession>();
	server->Run(serverEndpoint);
	client->Run(logEndpoint);

	Console::Log(Category::MMOServer, TEXT("MMO Server is running on ") + ToUnicodeString(serverEndpoint.toString()));

	GEngine->Run(4);
}
