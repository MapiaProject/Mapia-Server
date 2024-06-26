#include "pch.h"
#include "DataManager.hpp"

#include <filesystem>

DataManager::DataManager()
{
	m_datasheet = std::make_unique<SQLite::Database>("Common/Database/datasheet.db");
	/*auto path = ;
	if (sqlite3_open(path, &m_datasheet) != SQLITE_OK)
	{
		Console::Error(Category::MMOServer, TEXT("Can't load datasheet. please check is datasheet exists."));
		exit(0);
	}*/
}

void DataManager::Initialize()
{

}
