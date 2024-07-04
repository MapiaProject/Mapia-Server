#pragma once

class ObjectManager;
class MapManager;
class DataManager;
class DBManager;

class Manager
{
public:
	Manager();
	~Manager();
public:
	void Initialize();
	std::shared_ptr<ObjectManager> Object();
	std::shared_ptr<MapManager> Map();
	std::shared_ptr<DataManager> Data();
	std::shared_ptr<DBManager> Database();
private:
	std::shared_ptr<ObjectManager> m_object;
	std::shared_ptr<MapManager> m_map;
	std::shared_ptr<DataManager> m_data;
	std::shared_ptr<DBManager> m_db;
};

extern Manager* GManager;

