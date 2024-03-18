#pragma once

#include <Network/Session.hpp>
#include <generated/mmo/ServerPacketHandler.gen.hpp>

class Player;
class Room;

class GameSession : public Session
{
public:
	GameSession() = default;
	~GameSession() = default;
public:
	virtual void OnConnected(net::Endpoint) override;
	virtual void OnDisconnected(net::Endpoint) override;
	virtual void OnReceive(std::span<char>, int32) override;
public:
	__forceinline std::shared_ptr<Player> GetPlayer() { return m_player.lock(); }
	__forceinline std::shared_ptr<Room> GetRoom() { return m_room.lock(); }
	void SetPlayer(std::shared_ptr<Player> player);
	void SetRoom(std::shared_ptr<Room> room);
private:
	std::weak_ptr<Player> m_player;
	std::weak_ptr<Room> m_room;
};
