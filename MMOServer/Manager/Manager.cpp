#include "pch.h"
#include "Manager.hpp"

#include "ObjectManager.hpp"
#include "MapManager.hpp"
#include "DataManager.hpp"

Manager::Manager()
{
	m_object = MakeShared<ObjectManager>();
	m_map = MakeShared<MapManager>();
	m_data = MakeShared<DataManager>();
}

Manager::~Manager()
{
}

void Manager::Initialize()
{
	m_data->Initialize();
	m_object->Initialize();
	m_map->Initialize();
}

std::shared_ptr<ObjectManager> Manager::Object()
{
	return m_object;
}

std::shared_ptr<MapManager> Manager::Map()
{
	return m_map;
}

std::shared_ptr<DataManager> Manager::Data()
{
	return m_data;
}