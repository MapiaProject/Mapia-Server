#pragma once
#include <Thread/JobSerializer.hpp>
#include <generated/mmo/Protocol.gen.hpp>

class DatabaseManager : public JobSerializer
{
public:
	DatabaseManager();
	~DatabaseManager() = default;
public:
private:
	String m_connectionString = TEXT("DSN=HazardDB");
};

