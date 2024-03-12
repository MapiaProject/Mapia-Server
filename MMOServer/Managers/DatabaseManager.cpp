#include "pch.h"
#include "DatabaseManager.hpp"
#include "Database/DBConnectionPool.hpp"
#include "Database/Statement.hpp"
#include "Network/Session.hpp"

DatabaseManager::DatabaseManager()
{
	GEngine->GetDBConnectionPool()->Clear();

	GEngine->GetDBConnectionPool()->Connect(1, m_connectionString);
}