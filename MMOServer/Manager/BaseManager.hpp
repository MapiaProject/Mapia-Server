#pragma once
#include "Functor.hpp"
#include <memory>

template<class T>
class BaseManager : public Runnable<T>
{
public:
	virtual void Initialize() = 0;
};