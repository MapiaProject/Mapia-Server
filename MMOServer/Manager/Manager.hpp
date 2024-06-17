#pragma once

class NetObjectManager;
class MapManager;

class Manager
{
public:
	Manager();
	~Manager();
public:
	void Initialize();
	std::shared_ptr<NetObjectManager> Object();
	std::shared_ptr<MapManager> Map();
private:
	std::shared_ptr<NetObjectManager> m_netObject;
	std::shared_ptr<MapManager> m_map;
};

extern Manager* GManager;

