#pragma once

MAKE_LOG_CATEGORY(MMOServer);
struct MMOServer final
{
	MMOServer();
	~MMOServer();

	void Run();
};

static MMOServer* WOSServerInstance;