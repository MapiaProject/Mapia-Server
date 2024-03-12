#include "pch.h"
#include "MMOServer.hpp"
#include "Managers/Manager.hpp"

Engine* GEngine;
Manager* GManager;

MMOServer::MMOServer()
{
	GEngine = new Engine;
	GManager = new Manager;
}

MMOServer::~MMOServer()
{
	delete GEngine;
	delete GManager;
}
