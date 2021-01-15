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
	Entity ent = { ++number_of_entities };
	entities.push_back(ent);
	return ent;
}

void EntityFactory::DestroyEntity(Entity ent)
{
	//TODO - 
	// current implementation had no direct access to component indicies within vector, for O(n) deletion, where n is the total number of components
	// could obviously be improved beyond this initial implementation
	// add all components to large array or array of pointers to component arrays for simpler iteration

	//erase entity
	auto entityIterator = std::begin(entities);
	while (entityIterator != std::end(entities))
	{
		if (entityIterator->id = ent.id)
		{
			entities.erase(entityIterator);
			break;
		}
	}
	
	//erase transform if exists
	auto transformIterator = std::begin(transformComponents);
	while (transformIterator != std::end(transformComponents))
	{
		if (transformIterator->entity.id = ent.id)
		{
			transformComponents.erase(transformIterator);
			break;
		}
	}
}

Component* EntityFactory::AddComponent(Entity ent, std::string component_string)
{
	//TODO - should prevent adding duplicate component
	
	if (component_string == "TRANSFORM")
	{
		transformComponents.emplace_back();
		transformComponents.back().entity = ent;
		return &transformComponents.back();
	}

	//TODO - throw error
	return nullptr;
}

Component* EntityFactory::GetComponent(Entity ent, std::string component_string)
{
	// if this was a hybid system where each entity held a pointer to its components, this would be much faster access
	if (component_string == "TRANSFORM")
	{
		for (auto transform : transformComponents)
		{
			if (transform.entity.id = ent.id)
			{
				return &transform;
			}
		}
	}

	//TODO - throw error
	return nullptr;
}

void EntityFactory::RemoveComponent(Entity ent, std::string component_string)
{
	// if this was a hybid system where each entity held a pointer to its components, this would be much faster access
	// erase is also O(n) due to using a vector. could create a custom vector that marked location as deleted and replace on add

	if (component_string == "TRANSFORM")
	{
		auto i = std::begin(transformComponents);
		while (i != std::end(transformComponents))
		{
			if (i->entity.id = ent.id)
			{
				transformComponents.erase(i);
				break;
			}
		}
	}
}