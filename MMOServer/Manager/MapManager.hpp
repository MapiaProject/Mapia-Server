#pragma once
#include "Storage/GameMap.hpp"
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
	void Enter(std::shared_ptr<GameMap> map, std::shared_ptr<class Player> player);
private:
	HashMap<String, std::shared_ptr<GameMap>> m_mapData;
};

