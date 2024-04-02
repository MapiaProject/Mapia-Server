#include "pch.h"
#include "AccountManager.hpp"
#include "Manager.hpp"
#include "Database/DBConnectionPool.hpp"
#include "Database/DBConnection.hpp"
#include "Database/Statement.hpp"

AccountManager::AccountManager()
{
	auto conn = GEngine->GetDBConnectionPool()->Pop();
	auto stmt = conn->CreateStatement<0, 2>(TEXT("CALL SP_GetAccounts()"));

	WCHAR nickname[33] = TEXT("");
	WCHAR uid[37] = TEXT("");
	stmt.Bind(0, uid);
	stmt.Bind(1, nickname);
	
	ASSERT_CRASH(stmt.ExecuteQuery());
	while (stmt.Next())
	{
		m_users[uid] = nickname;
	}
}

AccountManager::~AccountManager()
{

}

std::optional<String> AccountManager::GetNickname(String uid)
{
	String nickname = m_users[uid];
	if (nickname == TEXT(""))
		return std::nullopt;
	return nickname;
}
