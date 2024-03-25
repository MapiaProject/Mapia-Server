#pragma once
#include <Room/Room.hpp>

enum
{
	MAX_PLAYER = 8
};

class GameRoom : public Room
{
	friend class RoomManager;
public:
	virtual void HandleEnter(std::shared_ptr<Session> session) override;
	virtual void HandleLeave(std::shared_ptr<Session> session) override;
};