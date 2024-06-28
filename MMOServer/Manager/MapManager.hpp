#pragma once
#include "BaseManager.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class MapManager : public BaseManager<MapManager>
{
public:
	MapManager();
public:
	std::shared_ptr<class GameMap> GetMap(String name);
public:
	void HandleEnter(std::shared_ptr<class Session> session, gen::mmo::EnterMapReq packet);
public:
	void Initialize() override;
private:
	ConcurrencyHashMap<String, std::shared_ptr<class GameMap>> m_mapData;
};

