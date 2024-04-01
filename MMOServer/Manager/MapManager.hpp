#pragma once
#include "Object/GameMap.hpp"
#include "Thread/JobSerializer.hpp"

#include "generated/mmo/Protocol.gen.hpp"

class MapManager : public JobSerializer
{
public:
	MapManager();
public:
	std::shared_ptr<GameMap> GetMap(String name);
public:
	void HandleEnter(std::shared_ptr<class Session> session, gen::mmo::EnterMapReq packet);
private:
	HashMap<String, std::shared_ptr<GameMap>> m_mapData;
};

