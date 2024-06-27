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
	const MonsterData& GetMonsterData(gen::mmo::EObjectType type);
	const Vector<ItemData>& GetDropsData(gen::mmo::EObjectType type);
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
	ConcurrencyHashMap<String, MonsterData> m_monsterInfoData;
	ConcurrencyHashMap<String, ItemData> m_itemInfoData;
	ConcurrencyHashMap<String, Vector<ItemData>> m_dropInfoData;
};

