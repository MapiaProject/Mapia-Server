#pragma once
#include "Thread/JobSerializer.hpp"
#include <memory>

template<class T>
class BaseManager :
	public JobSerializer
{
public:
	virtual void Initialize() = 0;
};