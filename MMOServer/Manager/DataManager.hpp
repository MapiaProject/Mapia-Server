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
	const SkillData& GetSkillData(gen::mmo::ESkillType type);
	const StatData& GetStatData(uint32 level);
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
	ConcurrencyHashMap<gen::mmo::EObjectType, MonsterData> m_monsterData;
	ConcurrencyHashMap<gen::mmo::EItemType, ItemData> m_itemData;
	ConcurrencyHashMap<gen::mmo::EObjectType, Vector<ItemData>> m_dropData;
	ConcurrencyHashMap<gen::mmo::ESkillType, SkillData> m_skillData;
	ConcurrencyHashMap<uint32, StatData> m_statData;
};

