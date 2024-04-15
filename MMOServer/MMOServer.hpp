#pragma once

MAKE_LOG_CATEGORY(MMOServer);
struct MMOServer final
{
	MMOServer();
	~MMOServer();
};

static MMOServer WOSServerInstance;