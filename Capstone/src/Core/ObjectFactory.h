#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "Component.h"
#include "Components/Components.h"

class Component;
class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	GameObject* CreateGameObject();
	void DestroyGameObject(GameObject*);
	void DestroyAllGameObjects();
	Component* AddComponent(GameObject*, Components::ComponentType);
	void RemoveComponent(GameObject*, Components::ComponentType);
	Component* GetComponent(GameObject*, Components::ComponentType);
	GameObject* CreatePlayer(int posx, int posy);
	GameObject* CreateProjectile(Vec2<float> position, std::string spritePath, Vec2<float> velocity, int layer);
	GameObject* GetPlayer();
	GameObject* CreateText(std::string text, int posx, int posy);
	GameObject* CreateButton(std::string text, int posx, int posy, int width, int height);
	GameObject* GetObjectByIndex(int index);
	GameObject* GetObjectByTag(std::string tag);
	std::vector<GameObject*> GetObjectsByTag(std::string);

	//std::vector<std::vector<Component>*> components;
	std::vector<GameObject> gameObjects;
	std::vector<Transform> transformComponents;
	std::vector<Sprite> spriteComponents;
	std::vector<Physics> physicsComponents;
	std::vector<PlayerController> playerComponents;
	std::vector<Collider> colliderComponents;
	std::vector<Health> healthComponents;
	std::vector<Damage> damageComponents;
	std::vector<EnemyController> enemyComponents;
	std::vector<Duration> durationComponents;
	std::vector<FilledBar> filledbarComponents;
	Input inputComponent;
};

