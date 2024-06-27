#pragma once
#include "BaseManager.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "Storage/Datasheet.hpp"
#include "generated/mmo/Enum.gen.hpp"

class DataManager : public BaseManager<DataManager>
{
public:
	DataManager();
public:
	void Initialize() override;
public:
	const MonsterInfo& GetMonsterInfo(gen::mmo::EObjectType type);
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
	HashMap<String, MonsterInfo> m_monsterInfoData;
};

