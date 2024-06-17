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
	NetObjectManager* Object();
	MapManager* Map();
private:
	NetObjectManager* m_netObject;
	MapManager* m_map;
};

extern Manager* GManager;

