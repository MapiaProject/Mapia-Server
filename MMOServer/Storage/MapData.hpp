#pragma once

enum class Block : uint8
{
	Air,
	Ground,
	SpawnArea,
	Portal,
	Entity,
	DropItem
};

struct Portal
{
	Portal(StringView dest, Point2DI pos) : destMap(dest), position(pos)
	{
	}
	String destMap;
	Point2DI position;
};

class MapData
{
public:
	MapData();
	MapData(StringView filename);
public:
	String GetName() const;
	void Read(StringView filename);
private:
	String m_name;
	Point2DI m_size;
	Vector<Vector<Block>> m_map;
	Vector<Portal> m_portals;
};

