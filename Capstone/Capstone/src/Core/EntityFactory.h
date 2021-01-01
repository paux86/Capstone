#pragma once
#include "Entity.h"
#include <vector>
#include <string>
#include "Components/Transform.h"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();
	Entity CreateEntity();
	void DestroyEntity();
	void AddComponent(Entity, std::string);
	void RemoveComponent(Entity, std::string);

private:
	std::vector<Entity> entities;
	std::vector<Transform> transformComponents;
};

