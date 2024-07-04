#include "pch.h"
#include "DBManager.hpp"

#include "Database/DBConnectionPool.hpp"

String DBManager::s_connectionStr = TEXT(
	"DRIVER={MySQL ODBC 8.3 Unicode Driver};"\
	"SERVER=localhost;"\
	"PORT=3306;"\
	"DATABASE=GameDB;"\
	"USER=GameAdmin;"\
	"PASSWORD=reWq0987.;"\
	"OPTION=3;"
);

DBManager::DBManager()
{
	m_connections = 10;
}

void DBManager::Initialize()
{
	if (!GEngine->GetDBConnectionPool()->Connect(m_connections, s_connectionStr))
	{
		Console::Error(Category::Database, TEXT("Failed to connect `GameDB`"));
	}
	Console::Log(Category::MMOServer, TEXT("'DBManager' initialized"));
}
