#pragma once
#include <string>

class GameObject;
class Component
{
public:
	Component() {}
	virtual ~Component() {};
	int gameObjectId;
	bool active = true;
};

