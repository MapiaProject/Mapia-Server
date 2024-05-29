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
	Portal(StringView dest, Vector2DI pos) : destMap(dest), position(pos)
	{
	}
	String destMap;
	Vector2DI position;
};

class MapData
{
public:
	MapData();
	MapData(StringView filename);
public:
	String GetName() const;
	Vector2DI GetSize() const;
	const Vector<Vector<Block>>& GetDataArray() const;
	void Read(StringView filename);
	std::optional<Block> GetBlock(Vector2DI position);
	Vector<Vector2DI> GetBlocks(Block block);
protected:
	String m_name;
	Vector2DI m_size;
	Vector<Vector<Block>> m_map;
	Vector<Portal> m_portals;
};

