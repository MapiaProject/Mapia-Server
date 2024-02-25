#pragma once
#include <Thread/JobSerializer.hpp>

class Player;

class Room : public JobSerializer
{
public:
	Room(String name);
public:
	bool HandleEnter(std::shared_ptr<Session> session);
	bool HandleLeave(std::shared_ptr<Session> session);
public:
	__forceinline String GetId() { return m_id; }
	__forceinline String GetName() { return m_name; }
private:
	String m_id;
	String m_name;
	Vector<std::shared_ptr<Player>> m_players;
};