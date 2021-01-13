#include "EntityFactory.h"
#include <iostream>


int EntityFactory::number_of_entities = 0;

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

Entity EntityFactory::CreateEntity()
{
	// any real reason to store entities?
	Entity ent = { ++number_of_entities };
	entities.push_back(ent);
	return ent;
}

void EntityFactory::DestroyEntity()
{
	// current implementation had no direct access to component indicies within vector, for O(n) deletion, where n is the total number of components
	// could obviously be improved beyond this initial implementation
}

Component* EntityFactory::AddComponent(Entity ent, std::string component_string)
{
	if (component_string == "TRANSFORM")
	{
		transformComponents.emplace_back();
		transformComponents.back().entity = ent;
		return &transformComponents.back();
	}

	return nullptr;
}

void EntityFactory::RemoveComponent(Entity, std::string)
{

}