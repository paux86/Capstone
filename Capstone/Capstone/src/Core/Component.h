#pragma once
#include "GameObject.h"
#include <string>

class GameObject;
class Component
{
public:
	virtual ~Component() {};
	std::string componentType;
	GameObject* p_GameObject;
};

