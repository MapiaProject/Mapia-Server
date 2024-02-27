#pragma once
#include <Thread/JobSerializer.hpp>

class Player;

enum
{
	MAX_PLAYER = 8
};

class Room : public JobSerializer
{
public:
	void Broadcast(class Packet* pk, uint32 exceptId = -1);
public:
	void HandleEnter(std::shared_ptr<Session> session);
	void HandleLeave(std::shared_ptr<Session> session);
public:
	static std::shared_ptr<Room> Create(uint32 id, StringView name);
	
	__forceinline uint32 GetId() { return m_id; }
	__forceinline String GetName() { return m_name; }
	
	void SetId(uint32 id);
	void SetName(StringView name);
private:
	uint32 m_id;
	String m_name;
	HashMap<uint32, std::shared_ptr<Player>> m_players;
};