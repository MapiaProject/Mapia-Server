#pragma once
#include <Thread/JobSerializer.hpp>
#include <generated/mmo/Enum.gen.hpp>

class Room : public JobSerializer
{
public:
	void Broadcast(class Packet* pk, uint32 exceptId = -1);
public:
	virtual void HandleEnter(std::shared_ptr<Session> session);
	virtual void HandleLeave(std::shared_ptr<Session> session);
	void HandleResult(Session* session, gen::mmo::ERoomEvent event, bool success);
public:
	static std::shared_ptr<Room> Create(uint32 id, StringView name);
	
	__forceinline uint32 GetId() { return m_id; }
	__forceinline String GetName() { return m_name; }
	
	void SetId(uint32 id);
	void SetName(StringView name);
protected:
	uint32 m_id;
	String m_name;
	uint32 lastPlayerId = 0;
	HashMap<uint32, std::shared_ptr<class Player>> m_players;
};