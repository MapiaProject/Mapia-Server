#pragma once
#include "magic_enum.hpp"
#include "generated/mmo/Enum.gen.hpp"

using namespace gen;

struct MonsterData
{
	MonsterData() = default;
	MonsterData(uint32 id, std::string_view type, uint32 hp, uint32 power, double attackRange)
		: id(id), type(*magic_enum::enum_cast<mmo::EObjectType>(type)), hp(hp), power(power), attackRange(attackRange)
	{}
	int32 id;
	mmo::EObjectType type;
	int32 hp;
	int32 power;
	double attackRange;
};

struct ItemData
{
	ItemData() = default;
	ItemData(uint32 id, std::string_view type)
		: id(id), type(*magic_enum::enum_cast<mmo::EItemType>(type))
	{}
	uint32 id;
	mmo::EItemType type;
};

struct SkillData
{
	SkillData() = default;
	SkillData(uint32 id, std::string_view type, uint32 damage, Vector2DF range)
		: id(id), type(*magic_enum::enum_cast<mmo::ESkillType>(type)), damage(damage), range(range)
	{}
	uint32 id;
	mmo::ESkillType type;
	uint32 damage;
	Vector2DF range;
};