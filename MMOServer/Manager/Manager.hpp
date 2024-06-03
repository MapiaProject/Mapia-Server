#pragma once

class NetObjectManager;
class MapManager;
class SessionManager;

class Manager
{
public:
	Manager();
	~Manager();
public:
	std::shared_ptr<NetObjectManager> Object();
	std::shared_ptr<MapManager> Map();
	std::shared_ptr<SessionManager> Session();
private:
	std::shared_ptr<NetObjectManager> m_netObject;
	std::shared_ptr<MapManager> m_map;
	std::shared_ptr<SessionManager> m_session;
};

extern Manager* GManager;

