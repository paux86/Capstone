#pragma once
#include "Component.h"
#include <vector>
#include <string>

class Component;
class GameObject
{
public:
	GameObject(int id);
	Component* GetComponent(std::string componentType);
	void AddComponent(Component* component);
	void RemoveComponent(std::string componentType);
	bool HasComponent(std::string componentType);
	const int object_id;

private:
	std::vector<Component*> components;
};

