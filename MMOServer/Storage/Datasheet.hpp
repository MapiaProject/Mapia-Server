#pragma once

struct MonsterInfo
{
	MonsterInfo() = default;
	MonsterInfo(uint32 id, StringView type, uint32 hp, uint32 power, double attackRange)
		: id(id), type(type), hp(hp), power(power), attackRange(attackRange)
	{}
	int32 id;
	String type;
	int32 hp;
	int32 power;
	double attackRange;
};

struct ItemInfo
{
	ItemInfo() = default;
	ItemInfo(StringView type, uint32 id, StringView descript)
		: type(type), id(id), descript(descript)
	{}
	String type;
	uint32 id;
	String descript;
};

struct DropInfo
{
	DropInfo() = default;
	DropInfo(uint32 monsterId, uint32 itemId)
		: monsterId(monsterId), itemId(itemId)
	{}
	uint32 monsterId;
	uint32 itemId;
};