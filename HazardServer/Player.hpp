#pragma once

class GameSession;

class Player
{
public:
	Player() = default;
public:
public:
	__forceinline uint32 GetId() { return m_id; }
	__forceinline String GetName() { return m_name; }
	void SetId(uint32 id);
	void SetName(StringView name);
	__forceinline std::shared_ptr<GameSession> GetSession() { return m_session; }
private:
	uint32 m_id;
	String m_name;
	std::shared_ptr<GameSession> m_session;
};