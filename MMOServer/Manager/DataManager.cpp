#include "pch.h"
#include "DataManager.hpp"

#include <filesystem>

#include "magic_enum/magic_enum.hpp"

DataManager::DataManager()
{
}

void DataManager::Initialize()
{
	try
	{
		m_datasheet = std::make_unique<SQLite::Database>("Common/Database/datasheet.db");
		{
			SQLite::Statement stmt(*m_datasheet, "SELECT id, ptype, hp, power, attackRange FROM monster");
			while (stmt.executeStep())
			{
				auto ptype = ToUnicodeString(stmt.getColumn(1).getString());
				MonsterData info(
					stmt.getColumn(0).getInt(),
					ptype,
					stmt.getColumn(2).getInt(),
					stmt.getColumn(3).getInt(),
					stmt.getColumn(4).getDouble()
				);
				m_monsterInfoData[ptype] = info;
			}
		}
		{
			SQLite::Statement stmt(*m_datasheet, "SELECT ptype, id FROM item");
			while (stmt.executeStep())
			{
				auto ptype = ToUnicodeString(stmt.getColumn(0).getString());
				ItemData info(
					ptype,
					stmt.getColumn(1).getInt()
				);
				m_itemInfoData[ptype] = info;
			}
		}
		{
			SQLite::Statement stmt(*m_datasheet,
				"SELECT m.ptype, i.ptype "\
				"FROM drops d "\
				"INNER JOIN monster m ON "\
				"d.monsterId = m.id "\
				"INNER JOIN item i ON "\
				"d.itemId = i.id"
			);
			while (stmt.executeStep())
			{
				auto monsterType = ToUnicodeString(stmt.getColumn(0).getString());
				auto itemType = ToUnicodeString(stmt.getColumn(1).getString());
				m_dropInfoData[monsterType].push_back(m_itemInfoData[itemType]);
			}
		}
		Console::Log(Category::MMOServer, TEXT("'DataManager' initialized"));
	}
	catch (std::exception&)
	{
		Console::Error(Category::MMOServer, TEXT("Can't load datasheet. please check is datasheet exists."));
		exit(0);
	}
}

const MonsterData& DataManager::GetMonsterData(gen::mmo::EObjectType type)
{
	return m_monsterInfoData[ToUnicodeString(magic_enum::enum_name(type))];
}

const Vector<ItemData>& DataManager::GetDropsData(gen::mmo::EObjectType type)
{
	return m_dropInfoData[ToUnicodeString(magic_enum::enum_name(type))];
}
