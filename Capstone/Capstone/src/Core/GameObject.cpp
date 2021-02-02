#include "GameObject.h"

GameObject::GameObject(int id) : object_id(id)
{

}

Component * GameObject::GetComponent(std::string componentType)
{
	for (auto component : components)
	{
		if (component->componentType == componentType)
		{
			return component;
		}
	}
	
	//TODO: throw error
	return nullptr;
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::RemoveComponent(std::string componentType)
{
	auto i = std::begin(components);

	while (i != std::end(components))
	{
		if ((*i)->componentType == componentType)
		{
			components.erase(i);
			break;
		}
	}
}

bool GameObject::HasComponent(std::string componentType)
{
	for (auto component : components)
	{
		if (component->componentType == componentType)
		{
			return true;
		}
	}

	return false;
}
