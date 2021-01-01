#pragma once
#include "Entity.h"
class Component
{
public:
	virtual ~Component() {};
	Entity entity;
};

