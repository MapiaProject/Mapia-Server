#pragma once

class Manager
{
public:
	Manager();
	~Manager();
public:
	__forceinline std::shared_ptr<class RoomManager> GetRoom() { return m_roomManager; }
	__forceinline std::shared_ptr<class DatabaseManager> GetDatabase() { return m_databaseManager; }
private:
	std::shared_ptr<class RoomManager> m_roomManager;
	std::shared_ptr<class DatabaseManager> m_databaseManager;
};

extern Manager* GManager;