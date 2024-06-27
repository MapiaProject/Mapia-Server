#include "pch.h"
#include "MMOServer.hpp"

int main()
{
	WOSServerInstance = new MMOServer;
	WOSServerInstance->Run();
	delete WOSServerInstance;
}