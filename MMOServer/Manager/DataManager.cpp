#include "pch.h"
#include "DataManager.hpp"

#include <filesystem>

#include "magic_enum/magic_enum.hpp"

DataManager::DataManager()
{
	try
	{
		m_datasheet = std::make_unique<SQLite::Database>("Common/Database/datasheet.db");
		SQLite::Statement stmt(*m_datasheet, "SELECT id, ptype, hp, power, attackRange FROM monster");
		while (stmt.executeStep())
		{
			auto id = stmt.getColumn(0).getInt();
			auto ptype = ToUnicodeString(stmt.getColumn(1).getString());
			auto hp = stmt.getColumn(2).getInt();
			auto power = stmt.getColumn(3).getInt();
			auto attackRange = stmt.getColumn(4).getDouble();
			MonsterInfo info(id, ptype, hp, power, attackRange);
			m_monsterInfoData[ptype] = info;
		}
	}
	catch (std::exception&)
	{
		Console::Error(Category::MMOServer, TEXT("Can't load datasheet. please check is datasheet exists."));
		exit(0);
	}

}

void DataManager::Initialize()
{

}

const MonsterInfo& DataManager::GetMonsterInfo(gen::mmo::EObjectType type)
{
	return m_monsterInfoData[ToUnicodeString(magic_enum::enum_name(type))];
}
