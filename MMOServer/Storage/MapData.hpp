#pragma once

enum class Block : uint8
{
	Air,
	Border,
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
	Point2DI GetSize() const;
	const Vector<Vector<Block>>& GetDataArray() const;
	void Read(StringView filename);
	Block GetBlock(Point2DI position);
protected:
	String m_name;
	Point2DI m_size;
	Vector<Vector<Block>> m_map;
	Vector<Portal> m_portals;
};

