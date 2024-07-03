#pragma once
#include "Thread/JobSerializer.hpp"
#include <memory>

class BaseManager :
	public JobSerializer
{
public:
	virtual void Initialize() = 0;
};