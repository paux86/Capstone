#pragma once
#include "Component.h"
#include "Components/Components.h"
#include <vector>
#include <string>
#include <tuple>


typedef std::tuple<Components::ComponentType, int> componentTuple;

class GameObject
{
public:
	GameObject(int id);
	int GetComponentIndex(Components::ComponentType componentType);
	void AddComponent(Components::ComponentType componentType, int index);
	void RemoveComponent(Components::ComponentType componentType);
	bool HasComponent(Components::ComponentType componentType);
	void UpdateComponentHandle(Components::ComponentType componentType, int handle);
	void AddTag(std::string tag);
	void RemoveTag(std::string tag);
	bool HasTag(std::string tag);
	
	int object_id;
	std::vector<std::string> tags;
	std::vector<componentTuple> components;
};

