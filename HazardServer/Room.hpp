#pragma once
#include <Thread/JobSerializer.hpp>
#include <generated/Enum.gen.hpp>

enum
{
	MAX_PLAYER = 8
};

class Room : public JobSerializer
{
	friend class RoomManager;
public:
	void Broadcast(class Packet* pk, uint32 exceptId = -1);
public:
	void HandleEnter(std::shared_ptr<Session> session);
	void HandleLeave(std::shared_ptr<Session> session);
	void HandleResult(Session* session, gen::ERoomEvent event, bool success);
public:
	static std::shared_ptr<Room> Create(uint32 id, StringView name);
	
	__forceinline uint32 GetId() { return m_id; }
	__forceinline String GetName() { return m_name; }
	
	void SetId(uint32 id);
	void SetName(StringView name);
private:
	uint32 m_id;
	String m_name;
	uint32 lastPlayerId = 0;
	HashMap<uint32, std::shared_ptr<class Player>> m_players;
	std::weak_ptr<class RoomManager> m_manager;
};

static Room Lobby;