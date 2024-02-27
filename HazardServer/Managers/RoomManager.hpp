#pragma once
#include <Thread/JobSerializer.hpp>

#include <generated/Protocol.gen.hpp>

class Room;

class RoomManager : public JobSerializer
{
public:
	RoomManager();
	~RoomManager();
public:
	void AddRoom(String name);
	void DestroyRoom(uint32 id);
public:
	/* HANDLING */
	void HandleEnterGame(std::shared_ptr<Session> session);
	void HandleRoomEvent(std::shared_ptr<Session> session, gen::RoomEventReq pk);
private:
	/* Key: uint32, Value: Room Ptr */
	HashMap<uint32, std::shared_ptr<Room>> m_roomList;
	uint32 m_lastId = 0;
};

