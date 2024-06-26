#pragma once

struct Ability
{
	uint32 hp;
	uint32 power;
};

struct MonsterInfo
{
	String type;
	uint32 id;
	Ability ability;
	Vector<uint32> drop;
};

struct ItemInfo
{
	String type;
	uint32 id;
	String descript;
};

struct DropInfo
{
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