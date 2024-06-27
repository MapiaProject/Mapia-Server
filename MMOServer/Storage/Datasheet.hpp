#pragma once

struct Ability
{
	Ability(uint32 hp, uint32 power)
		: hp(hp), power(power) 
	{}
	uint32 hp;
	uint32 power;
};

struct MonsterInfo
{
	MonsterInfo(StringView type, uint32 id, Ability ability, Vector<uint32> drop)
		: type(type), id(id), ability(ability), drop(drop)
	{}
	String type;
	uint32 id;
	Ability ability;
	Vector<uint32> drop;
};

struct ItemInfo
{
	ItemInfo(StringView type, uint32 id, StringView descript)
		: type(type), id(id), descript(descript)
	{}
	String type;
	uint32 id;
	String descript;
};

struct DropInfo
{
	DropInfo(uint32 monsterId, uint32 itemId)
		: monsterId(monsterId), itemId(itemId)
	{}
	uint32 monsterId;
	uint32 itemId;
};

struct Datasheet
{
	Datasheet(StringView path) {};
	virtual void Read() {};
};

class ItemData : public Datasheet
{
public:
	ItemData(StringView path);
public:
	void Read() override;
private:
	HashMap<uint16, ItemInfo> m_item;
};

class MonsterData : public Datasheet
{
public:
	MonsterData(StringView path);
public:
	void Read() override;
private:
	HashMap<uint16, MonsterInfo> m_item;
};