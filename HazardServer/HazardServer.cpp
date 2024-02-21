#include "pch.h"
#include "HazardServer.hpp"

Engine* GEngine;

HazardServer::HazardServer()
{
	GEngine = new Engine;
}

HazardServer::~HazardServer()
{
	delete GEngine;
}
