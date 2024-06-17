#pragma once
#include "Thread/JobSerializer.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class NetObjectManager : public JobSerializer
{
public:
	NetObjectManager();
public:
	template<class T, class... Args>
	std::shared_ptr<T> Create(Args&&... args)
	{
		auto object = MakeShared<T>(++m_lastId, std::forward<Args>(args)...);
		m_objects.insert({ m_lastId, object });
		return object;
	}
	void RemoveObject(uint64 id);
	std::shared_ptr<class NetObject> GetObjectById(uint64 id);
public:
	void HandleEnterGame(std::shared_ptr<class Session> session, gen::mmo::EnterGameReq req);
	void HandleDirectChat(std::shared_ptr<class Session> session, gen::mmo::Chat chat);
	void HandleAllChat(std::shared_ptr<class Session> session, gen::mmo::Chat chat);
private:
	void BroadcastAll(Packet* packet, uint64 ignore = 0);
private:
	std::atomic<uint64> m_lastId;
	ConcurrencyHashMap<uint64, std::shared_ptr<class NetObject>> m_objects;
};

