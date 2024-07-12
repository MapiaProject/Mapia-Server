#pragma once
#include "Subsystem/GameInstance.hpp"

MAKE_LOG_CATEGORY(MMOServer);
struct MMOServer final : public GameInstance
{
	MMOServer();
	~MMOServer();

	void Run();
};

static MMOServer* WOSServerInstance;