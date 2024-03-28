#include "pch.h"
#include "MMOServer.hpp"
#include "Manager/Manager.hpp"

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
