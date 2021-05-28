#include "GameObject.h"
#include <algorithm>


GameObject::GameObject(int id) : object_id(id)
{
	
}

int GameObject::GetComponentIndex(Components::ComponentType componentType)
{	
	if (!components.empty())
	{
		for (componentTuple& component : components)
		{
			if (std::get<0>(component) == componentType)
			{
				return std::get<1>(component);
			}
		}
	}
	
	//TODO: throw error
	return -1;
}

void GameObject::AddComponent(Components::ComponentType componentType, int index)
{
	components.push_back(componentTuple(componentType, index));
}

void GameObject::RemoveComponent(Components::ComponentType componentType)
{
	auto i = std::begin(components);

	while (i != std::end(components))
	{
		if (std::get<0>(*i) == componentType)
		{
			components.erase(i);
			break;
		}
		i++;
	}
}

bool GameObject::HasComponent(Components::ComponentType componentType)
{
	if (!components.empty())
	{
		for (componentTuple& component : components)
		{
			if (std::get<0>(component) == componentType)
			{
				return true;
			}
		}
	}

	return false;
}

void GameObject::UpdateComponentHandle(Components::ComponentType componentType, int handle)
{
	for (auto& component : components)
	{
		if (std::get<0>(component) == componentType)
		{
			//printf("GameObject with id %d component %d reassigned from id %d to %d\n", object_id, componentType, std::get<1>(component), handle);
			std::get<1>(component) = handle;
			break;
		}
	}
}

void GameObject::AddTag(std::string tag)
{
	if (!HasTag(tag))
	{
		tags.push_back(tag);
	}
}

void GameObject::RemoveTag(std::string tag)
{
	if (HasTag(tag))
	{
		tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
	}
}

bool GameObject::HasTag(std::string tag)
{
	for (auto t : tags)
	{
		if (t == tag)
		{
			return true;
		}
	}
	return false;
}
