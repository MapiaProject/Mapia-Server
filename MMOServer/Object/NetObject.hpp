#pragma once

class NetObject
{
public:
	NetObject(uint64 id);
public:
	uint64 GetId() const;
	void SetId(uint64 id);
private:
	uint64 m_objectId;
};

