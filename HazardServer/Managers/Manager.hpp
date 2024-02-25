#pragma once

class Room;
class RoomManager;

class Manager
{
public:
	Manager();
	~Manager();
public:
	__forceinline std::shared_ptr<RoomManager> GetRoom() { return m_roomManager; }
private:
	std::shared_ptr<RoomManager> m_roomManager;
};

extern Manager* GManager;