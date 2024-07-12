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
	const uint32& GetRequireExp(uint32 level);
	const StatData& GetStatData(uint32 level);
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
	HashMap<gen::mmo::EObjectType, MonsterData> m_monsterData;
	HashMap<gen::mmo::EItemType, ItemData> m_itemData;
	HashMap<gen::mmo::EObjectType, Vector<ItemData>> m_dropData;
	HashMap<gen::mmo::ESkillType, SkillData> m_skillData;
	HashMap<uint32, uint32> m_levelUpExp;
	HashMap<uint32, StatData> m_statData;
};

