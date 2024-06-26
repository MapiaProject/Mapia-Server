#pragma once
#include "Thread/JobSerializer.hpp"
#include <memory>

template<class T>
class BaseManager :
	public std::enable_shared_from_this<T>,
	public JobSerializer
{
public:
	virtual void Initialize() = 0;
};