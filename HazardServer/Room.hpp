#pragma once
#include <Thread/JobSerializer.hpp>

class Room : public JobSerializer
{
public:
	Room(String name);
public:
private:
	String m_name;
};