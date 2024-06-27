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
	ItemData(StringView type, uint32 id)
		: type(type), id(id)
	{}
	String type;
	uint32 id;
};