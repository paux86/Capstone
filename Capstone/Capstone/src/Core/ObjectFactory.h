#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "Component.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	GameObject* CreateGameObject();
	void DestroyGameObject(GameObject*);
	Component* AddComponent(GameObject*, std::string);
	void RemoveComponent(GameObject*, std::string);

	std::vector<Transform> transformComponents;
	std::vector<Sprite> spriteComponents;

private:
	int next_gameObject_id;
	std::vector<GameObject> gameObjects;
};

