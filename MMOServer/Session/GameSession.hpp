#pragma once

#include <Network/Session.hpp>
#include <generated/mmo/ServerPacketHandler.gen.hpp>

class Player;

enum class RpcTarget : uint8
{
	All,
	Other
};

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
	void SetPlayer(std::shared_ptr<Player> player);
	std::shared_ptr<Player> GetPlayer();
private:
	std::shared_ptr<Player> m_player;
};
