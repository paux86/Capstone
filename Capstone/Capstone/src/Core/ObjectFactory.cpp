#include "ObjectFactory.h"
#include <iostream>



ObjectFactory::ObjectFactory()
{
	next_gameObject_id = 0;
}

ObjectFactory::~ObjectFactory()
{
	//TODO: destroy all components
}

GameObject* ObjectFactory::CreateGameObject()
{
	gameObjects.emplace_back(next_gameObject_id++);
	return &gameObjects.back();
}

void ObjectFactory::DestroyGameObject(GameObject* gameObject)
{
	//TODO:

	//for each pointer to component, destroy component

	//destroy gameobject
	
}

Component* ObjectFactory::AddComponent(GameObject* obj, std::string component_string)
{
	//TODO: should prevent adding duplicate component
	
	if (component_string == "TRANSFORM")
	{
		transformComponents.emplace_back();
		transformComponents.back().p_GameObject = obj;
		obj->AddComponent(&transformComponents.back());
		return &transformComponents.back();
	}

	//TODO: throw error if invalid component name
	return nullptr;
}

void ObjectFactory::RemoveComponent(GameObject* obj, std::string component_string)
{
	//TODO: shouldn't be hardcoding this, need to create vector of component types and search passed component vector name
	// erase is also O(n) due to using a vector. could create a custom vector that marked location as deleted and replace on add

	if (component_string == "TRANSFORM")
	{
		//remove from gameobject
		obj->RemoveComponent(component_string);

		//remove from transformComponents vector
		auto i = std::begin(transformComponents);
		while (i != std::end(transformComponents))
		{
			if (i->p_GameObject->object_id == obj->object_id)
			{
				transformComponents.erase(i);
				break;
			}
		}
	}
}