#pragma once
class AccountManager
{
public:
	AccountManager();
	~AccountManager();
public:
	std::optional<String> GetNickname(String uid);
private:
	HashMap<String, String> m_users;
};

