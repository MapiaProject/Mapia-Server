#pragma once

class ObjectManager;
class MapManager;
class DataManager;

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
private:
	std::shared_ptr<ObjectManager> m_object;
	std::shared_ptr<MapManager> m_map;
	std::shared_ptr<DataManager> m_data;
};

extern Manager* GManager;

