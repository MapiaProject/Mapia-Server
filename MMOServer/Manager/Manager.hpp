#pragma once

class NetObjectManager;
class MapManager;
class AccountManager;

class Manager
{
public:
	Manager();
	~Manager();
public:
	std::shared_ptr<NetObjectManager> NetObject();
	std::shared_ptr<MapManager> Map();
	std::shared_ptr<AccountManager> Account();
private:
	std::shared_ptr<NetObjectManager> m_netObject;
	std::shared_ptr<MapManager> m_map;
	std::shared_ptr<AccountManager> m_accountManager;
};

extern Manager* GManager;

