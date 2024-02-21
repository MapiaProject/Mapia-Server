#pragma once
#include <Thread/JobSerializer.hpp>

class Room : public JobSerializer
{
public:
	Room() = default;
public:
	void Enter();
	void Leave();
	void Behaviour();
};

extern std::shared_ptr<Room> GRoom;