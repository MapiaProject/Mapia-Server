#include "pch.h"
#include "MMOServer.hpp"
#include "Manager/Manager.hpp"
#include "Database/DBConnectionPool.hpp"

Engine* GEngine;
Manager* GManager;

MMOServer::MMOServer()
{
	GEngine = new Engine;
	GEngine->Initialize();

	GEngine->GetDBConnectionPool()->Connect(10, TEXT(
		"DRIVER={MySQL ODBC 8.3 Unicode Driver};"
		"SERVER=localhost;"
		"PORT=3306;"
		"DATABASE=GameDB;"
		"USER=GameAdmin;"
		"PASSWORD=reWq0987.;"
		"OPTION=3;"
	));
	GManager = new Manager;
	GManager->Initialize();
}

MMOServer::~MMOServer()
{
	delete GEngine;
	delete GManager;
}
