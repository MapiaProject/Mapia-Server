#include "pch.h"
#include "MapData.hpp"

#include "Util/Parser/Ini.hpp"

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

const Vector<Vector<Block>>& MapData::GetMap() const
{
	return m_map;
}

void MapData::Read(StringView filename)
{
	auto ini = Ini(TEXT("common/generated/maps/") + String(filename));
	auto section = ini[TEXT("info")];

	/* load map info */
	m_name = section.Get<String>(TEXT("name"));

	auto sp = action::Split(section.Get<String>(TEXT("size")), TEXT(','));
	m_size = Point2DI(std::stoi(sp[0]), std::stoi(sp[1]));

	auto portalsStr = section.Get<String>(TEXT("portal"));
	auto portals = action::Split(portalsStr, TEXT(','));
	/*---------------*/

	/* load map data */
	auto map = ini[TEXT("map")].Get<String>(TEXT("data"));

	for (int i = 0; i < m_size.GetY(); ++i)
	{
		Vector<Block> t(m_size.GetX());
		auto submap = map.substr(i * m_size.GetX(), m_size.GetX());
		std::transform(submap.begin(), submap.end(), t.begin(), [&, x = 0, cnt = 0](const auto& wc) mutable
		{
			auto block = static_cast<Block>(wc - L'0');
			if (block == Block::Portal)
				m_portals.push_back(Portal(portals[cnt++], Point2DI(x, i)));
			++x;

			return block;
		});
		m_map.push_back(t);
	}
	/* ------------- */
}