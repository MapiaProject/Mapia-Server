#pragma once
class AccountManager
{
public:
	AccountManager();
	~AccountManager();
public:
	std::optional<String> GetNickname(String uid);
	void UpdateData();
private:
	HashMap<String, String> m_userAccount;
};

