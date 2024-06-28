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
	const List<ItemData>& GetDropsData(gen::mmo::EObjectType type);
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
	ConcurrencyHashMap<uint32, MonsterData> m_monsterInfoData;
	ConcurrencyHashMap<uint32, ItemData> m_itemInfoData;
	ConcurrencyHashMap<uint32, List<ItemData>> m_dropInfoData;
};

