#pragma once
#include "BaseManager.hpp"
#include "generated/mmo/Protocol.gen.hpp"

class ObjectManager : public BaseManager<ObjectManager>
{
public:
	ObjectManager();
public:
	template<class T, class... Args>
	std::shared_ptr<T> Create(Args&&... args)
	{
		auto object = MakeShared<T>(++m_lastId, std::forward<Args>(args)...);
		m_objects.insert({ m_lastId, object });
		return object;
	}
	void Initialize() override;
	void RemoveObject(uint64 id);
	std::shared_ptr<class GameObject> GetObjectById(uint64 id);
public:
	void HandleEnterGame(class Session* session, std::shared_ptr<gen::mmo::EnterGameReq> req);
	void HandleDirectChat(class Session* session, std::shared_ptr<gen::mmo::Chat> chat);
	void HandleAllChat(class Session* session, std::shared_ptr<gen::mmo::Chat> chat);
private:
	void BroadcastAll(Packet* packet, uint64 ignore = 0);
private:
	std::atomic<uint64> m_lastId;
	ConcurrencyHashMap<uint64, std::shared_ptr<class GameObject>> m_objects;
};

