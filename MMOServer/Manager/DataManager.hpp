#pragma once
#include "BaseManager.hpp"
#include "SQLiteCpp/SQLiteCpp.h"

class DataManager : public BaseManager<DataManager>
{
public:
	DataManager();
public:
	void Initialize() override;
private:
	std::unique_ptr<SQLite::Database> m_datasheet;
};

