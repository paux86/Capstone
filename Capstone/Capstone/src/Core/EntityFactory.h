#pragma once
#include "Entity.h"
#include <vector>
#include <string>
#include "Component.h"
#include "Components/Transform.h"

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();
	Entity CreateEntity();
	void DestroyEntity(Entity);
	Component* AddComponent(Entity, std::string);
	Component* GetComponent(Entity, std::string);
	void RemoveComponent(Entity, std::string);

private:
	static int number_of_entities;
	std::vector<Entity> entities;
	std::vector<Transform> transformComponents;
};

