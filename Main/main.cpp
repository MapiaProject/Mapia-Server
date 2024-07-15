#include "pch.h"
#include "MMOServer.hpp"

int main()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(500ms); // Wait for LogServer

	NeonlightServerInstance = new MMOServer;
	NeonlightServerInstance->Run();

	delete NeonlightServerInstance;
}