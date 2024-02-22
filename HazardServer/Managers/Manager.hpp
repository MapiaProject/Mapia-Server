#pragma once

class Room;

class Manager
{
public:
	Manager();
	~Manager();
public:
	void MakeRoom(String id, String name);
	void DestroyRoom(String id);
	__forceinline Room* GetRoom(String id) { return m_roomList[id]; }
	Vector<String> GetRoomList();
private:
	ConcurrencyHashMap<String, Room*> m_roomList;
};

extern std::unique_ptr<Manager> GManager;