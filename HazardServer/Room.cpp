#include "pch.h"
#include "Room.hpp"

#include "uuid.hpp"

Room::Room(String name) : m_name(name), m_id(uuid::generate_uuid_v4())
{
}

bool Room::HandleEnter(std::shared_ptr<Session> session)
{
	return false;
}

bool Room::HandleLeave(std::shared_ptr<Session> session)
{
	return false;
}
