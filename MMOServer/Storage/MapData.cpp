#include "pch.h"
#include "MapData.hpp"

#include "Util/Parser/Ini.hpp"
#include "magic_enum.hpp"
#include <ranges>

MapData::MapData() : m_size(0, 0)
{
}

MapData::MapData(StringView filename) : MapData()
{
	Read(filename);
}

String MapData::GetName() const
{
	return m_name;
}

Vector2DI MapData::GetSize() const
{
	return m_size;
}

const Deque<Vector<Block>>& MapData::GetDataArray() const
{
	return m_map;
}

void MapData::Read(StringView filename)
{
	auto ini = Ini { filename };
	auto section = ini[TEXT("info")];

	/* load map info */
	m_name = section.Get<String>(TEXT("name"));

	auto sp = Split(section.Get<String>(TEXT("size")), TEXT(','));
	m_size = Vector2DI(std::stoi(sp[0]), std::stoi(sp[1]));

	auto portalsStr = section.Get<String>(TEXT("portal"));
	auto portals = Split(portalsStr, TEXT(','));

	m_spawnMonster = section.Get<String>(TEXT("monster"));
	/*---------------*/

	/* load map data */
	auto map = ini[TEXT("map")].Get<String>(TEXT("data"));

	for (int i = 0; i < m_size.y; ++i)
	{
		Vector<Block> t(m_size.x);
		auto submap = map.substr(i * m_size.x, m_size.x);
		std::transform(submap.begin(), submap.end(), t.begin(), [&, x = 0, cnt = 0](const auto& wc) mutable
		{
			auto block = static_cast<Block>(wc - L'0');
			switch (block)
			{
			case Block::Portal:
				m_portals.push_back(Portal(portals[cnt++], Vector2DI(x, m_size.y - i - 1)));
				break;
			default:
				break;
			}
			++x;
			return block;
		});
		m_map.push_front(t);
	}
	/* ------------- */
}

std::optional<Block> MapData::GetBlock(Vector2DI position)
{
	if (position.x < 0 || position.y < 0 ||
		position.x >= m_size.x || position.y >= m_size.y)
		return std::nullopt;
	return m_map[position.y][position.x];
}

Vector<Vector2DI> MapData::GetBlocks(Block block)
{
	Vector<Vector2DI> res;
	for (int i = 0; i < m_map.size(); ++i)
	{
		for (int j = 0; j < m_map[i].size(); ++j)
		{
			if (m_map[i][j] == block)
				res.emplace_back(j, i);
		}
	}
	return res;
}

std::optional<mmo::EObjectType> MapData::GetSpawnMonster() const
{
	return magic_enum::enum_cast<mmo::EObjectType>(
		ToAnsiString(m_spawnMonster)
	);
}
