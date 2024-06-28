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
				auto id = stmt.getColumn(0).getInt();
				MonsterData info(
					id,
					stmt.getColumn(1).getString(),
					stmt.getColumn(2).getInt(),
					stmt.getColumn(3).getInt(),
					stmt.getColumn(4).getDouble()
				);
				m_monsterInfoData[id] = info;
			}
		}
		{
			SQLite::Statement stmt(*m_datasheet, "SELECT ptype, id FROM item");
			while (stmt.executeStep())
			{
				uint32 id = stmt.getColumn(1).getUInt();
				ItemData info(
					id,
					stmt.getColumn(0).getString()
				);
				m_itemInfoData[id] = info;
			}
		}
		{
			SQLite::Statement stmt(*m_datasheet,
				"SELECT m.id, i.id "\
				"FROM drops d "\
				"INNER JOIN monster m ON "\
				"d.monsterId = m.id "\
				"INNER JOIN item i ON "\
				"d.itemId = i.id"
			);
			while (stmt.executeStep())
			{
				auto monsterId = stmt.getColumn(0).getInt();
				auto itemId = stmt.getColumn(1).getInt();
				m_dropInfoData[monsterId].push_back(m_itemInfoData[itemId]);
			}
		}
		Console::Log(Category::MMOServer, TEXT("'DataManager' initialized"));
	}
	catch (std::exception&)
	{
		Console::Error(Category::MMOServer, TEXT("Can't load datasheet properly. please check datasheet."));
	}

}

const MonsterData& DataManager::GetMonsterData(gen::mmo::EObjectType type)
{
	return m_monsterInfoData[type];
}

const List<ItemData>& DataManager::GetDropsData(gen::mmo::EObjectType type)
{
	return m_dropInfoData[type];
}
