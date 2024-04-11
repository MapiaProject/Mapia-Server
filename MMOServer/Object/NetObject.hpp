#pragma once

class NetObject : public std::enable_shared_from_this<NetObject>
{
public:
	NetObject() = default;
	NetObject(uint64 id);
public:
	uint64 GetId() const;
	void SetId(uint64 id);
private:
	uint64 m_objectId;
};

