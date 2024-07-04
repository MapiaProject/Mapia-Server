#pragma once
#include "BaseManager.hpp"
#include "Database/Statement.hpp"

class DBManager : public BaseManager
{
public:
	DBManager();
public:
	void Initialize() override;
	template<int32 param, int32 column>
	Statement<param, column> CreateStatement(StringView sql)
	{
		auto conn = GEngine->GetDBConnectionPool()->Pop();
		if (!conn)
		{
			m_connections *= 2;
			GEngine->GetDBConnectionPool()->Connect(m_connections, s_connectionStr);
		}
		return conn->CreateStatement<param, column>(sql.data());
	}
private:
	uint32 m_connections;
	static String s_connectionStr;
};

