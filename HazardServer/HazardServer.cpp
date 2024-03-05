#include "pch.h"
#include "HazardServer.hpp"
#include "Managers/Manager.hpp"

Engine* GEngine;
Manager* GManager;

HazardServer::HazardServer()
{
	GEngine = new Engine;
	GManager = new Manager;
}

HazardServer::~HazardServer()
{
	delete GEngine;
	delete GManager;
}
