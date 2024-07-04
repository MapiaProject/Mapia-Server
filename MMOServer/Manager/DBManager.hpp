#pragma once
#include "BaseManager.hpp"
#include "Database/Statement.hpp"

class DBManager : public BaseManager
{
	template<uint32 N>
	struct ArgSpace
	{
		constexpr static String value() { return ArgSpace<N - 1>::value() + TEXT(", {}"); }
	};

	template<>
	struct ArgSpace<1>
	{
		constexpr static String value() { return TEXT("{}"); }
	};

public:
	DBManager();
public:
	void Initialize() override;

	class DBConnection* GetConnection();

	void ExecuteQuery(StringView sql);

	template<class... Args>
	void CallProcedure(String procedureName, Args&&... args)
	{
		constexpr auto size = sizeof...(Args);
		ExecuteQuery(
			std::format(TEXT("CALL {}({})"),
				procedureName,
				ArgSpace<size>::value(),
				std::forward<Args>(args)...
			)
		);
	}

	template<int32 Param, int32 Column>
	Statement<Param, Column> CreateStatement(StringView sql)
	{
		auto conn = GetConnection();
		return conn->CreateStatement<Param, Column>(sql.data());
	}
private:
	uint32 m_connections;
	static String s_connectionStr;
};

