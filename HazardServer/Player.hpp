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
	__forceinline std::shared_ptr<GameSession> GetSession() { return m_session.lock(); }
private:
	uint32 m_id;
	String m_name;
	std::weak_ptr<GameSession> m_session;
};