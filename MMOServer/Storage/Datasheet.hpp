#pragma once

struct MonsterData
{
	MonsterData() = default;
	MonsterData(uint32 id, StringView type, uint32 hp, uint32 power, double attackRange)
		: id(id), type(type), hp(hp), power(power), attackRange(attackRange)
	{}
	int32 id;
	String type;
	int32 hp;
	int32 power;
	double attackRange;
};

struct ItemData
{
	ItemData() = default;
	ItemData(uint32 id, StringView type)
		: id(id), type(type)
	{}
	uint32 id;
	String type;
};