#pragma once
#include "Thread/JobSerializer.hpp"
#include "Object/NetObject.hpp"

#include "generated/mmo/Protocol.gen.hpp"

class NetObjectManager : public JobSerializer
{
public:
	NetObjectManager();
public:
	template<class T>
	std::shared_ptr<NetObject> Create()
	{
		std::shared_ptr<NetObject> netObj = std::make_shared<T>(++m_lastId);
		m_objects[m_lastId] = netObj;

		return netObj;
	}
public:
	void HandleEnterGameReq(std::shared_ptr<class Session> session, gen::mmo::EnterGameReq req);
private:
	uint64 m_lastId;
	HashMap<uint64, std::weak_ptr<NetObject>> m_objects;
};

