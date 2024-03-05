#include "pch.h"
#include "Player.hpp"

void Player::SetId(uint32 id)
{
	m_id = id;
}

void Player::SetName(StringView name)
{
	m_name = name;
}
