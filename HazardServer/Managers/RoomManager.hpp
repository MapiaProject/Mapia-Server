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
	bool AddRoom(std::shared_ptr<Room> room);
public:
	/* HANDLING */
	void HandleEnterGame(std::shared_ptr<Session> session);
	void HandleRoomEvent(std::shared_ptr<Session> session, gen::AddRoomEvent pk);
private:
	/* Key: UUID, Value: ::Room Ptr */
	HashMap<String, std::shared_ptr<Room>> m_roomList;
};

