#pragma once
#include "BaseManager.hpp"
#include "Database/Statement.hpp"

class DBManager : public BaseManager
{
public:
	DBManager();
public:
	void Initialize() override;

	class DBConnection* GetConnection();

	void ExecuteQuery(StringView sql);

	template<int32 param, int32 column>
	Statement<param, column> CreateStatement(StringView sql)
	{
		auto conn = GetConnection();
		return conn->CreateStatement<param, column>(sql.data());
	}
private:
	uint32 m_connections;
	static String s_connectionStr;
};

