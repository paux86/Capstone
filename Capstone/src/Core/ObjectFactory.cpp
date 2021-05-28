#include "ObjectFactory.h"
#include <iostream>
#include <SDL.h>
#include "Components/CollisionLayer.h"


ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
	//DestroyAllGameObjects();
}

GameObject* ObjectFactory::CreateGameObject()
{
	gameObjects.emplace_back(gameObjects.size());
	//printf("Assigned id: %d\n", gameObjects.back().object_id);
	return &gameObjects.back();
}

void ObjectFactory::DestroyGameObject(GameObject* gameObject)
{
	//destroy all components
	for (auto componentType : Components::All)
	{
		//printf("Removing component %d from object %d\n", componentType, gameObject->object_id);
		RemoveComponent(gameObject, componentType);
	}

	//destroy gameobject and update object ids
	int gameObjectIndex = gameObject->object_id;
	auto i = std::begin(gameObjects) + gameObjectIndex;
	gameObjects.erase(i);

	int numberOfGameObjects = gameObjects.size();
	for (int i = gameObjectIndex; i < numberOfGameObjects; i++)
	{
		//printf("Updating game object with id %d to new id %d\n", gameObjects.at(i).object_id, i);
		gameObjects.at(i).object_id = i;
		for (auto& componentTuple : gameObjects.at(i).components)
		{
			GetComponent(&gameObjects.at(i), std::get<0>(componentTuple))->gameObjectId = i;
		}
	}
}

void ObjectFactory::DestroyAllGameObjects()
{
	int i = gameObjects.size() - 1;
	for (; i >= 0; i--)
	{
		DestroyGameObject(&gameObjects.at(i));
	}
}

//TODO: add 3rd void parmeter for instantiation
Component* ObjectFactory::AddComponent(GameObject* obj, Components::ComponentType componentType)
{
	//TODO: should prevent adding duplicate component
	//TODO: try and make this more programatic

	switch (componentType)
	{
		case Components::TRANSFORM:
			transformComponents.emplace_back();
			transformComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, transformComponents.size()-1);
			return &transformComponents.back();
			break;
		case Components::SPRITE:
			spriteComponents.emplace_back();
			spriteComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, spriteComponents.size() - 1);
			return &spriteComponents.back();
			break;
		case Components::PHYSICS:
			physicsComponents.emplace_back();
			physicsComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, physicsComponents.size() - 1);
			return &physicsComponents.back();
			break;
		case Components::INPUT:
			obj->AddComponent(componentType, 0);
			return &inputComponent;
			break;
		case Components::PLAYERCONTROLLER:
			playerComponents.emplace_back();
			playerComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, playerComponents.size() - 1);
			return &playerComponents.back();
			break;
		case Components::COLLIDER:
			colliderComponents.emplace_back();
			colliderComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, colliderComponents.size() - 1);
			return &colliderComponents.back();
			break;
		case Components::HEALTH:
			healthComponents.emplace_back();
			healthComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, healthComponents.size() - 1);
			return &healthComponents.back();
			break;
		case Components::DAMAGE:
			damageComponents.emplace_back();
			damageComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, damageComponents.size() - 1);
			return &damageComponents.back();
			break;
		case Components::ENEMYCONTROLLER:
			enemyComponents.emplace_back();
			enemyComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, enemyComponents.size() - 1);
			return &enemyComponents.back();
			break;
		case Components::DURATION:
			durationComponents.emplace_back();
			durationComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, durationComponents.size() - 1);
			return &durationComponents.back();
			break;
		case Components::FILLEDBAR:
			filledbarComponents.emplace_back();
			filledbarComponents.back().gameObjectId = obj->object_id;
			obj->AddComponent(componentType, filledbarComponents.size() - 1);
			return &filledbarComponents.back();
			break;
		default:
			return nullptr;
	}
}

void ObjectFactory::RemoveComponent(GameObject* obj, Components::ComponentType componentType)
{
	//TODO: shouldn't be hardcoding this, need to create vector of component types and search passed component vector name
	// erase is also O(n) due to using a vector. could create a custom vector that marked location as deleted and replace on add

	switch (componentType)
	{
	case Components::TRANSFORM:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(transformComponents) + componentIndex;
			transformComponents.erase(i);

			//update component handles
			int componentLength = transformComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[transformComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::SPRITE:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//TODO: should be handled in render system if possble perhaps?
			SDL_DestroyTexture(spriteComponents.at(componentIndex).spriteTexture);

			//remove from gameobject
			obj->RemoveComponent(componentType);
			
			//remove from transformComponents vector
			auto i = std::begin(spriteComponents) + componentIndex;
			spriteComponents.erase(i);

			//update component handles
			int componentLength = spriteComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[spriteComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::PHYSICS:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(physicsComponents) + componentIndex;
			physicsComponents.erase(i);

			//update component handles
			int componentLength = physicsComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[physicsComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::INPUT:
		if (obj->HasComponent(componentType))
		{
			obj->RemoveComponent(componentType);
		}
		break;
	case Components::PLAYERCONTROLLER:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(playerComponents) + componentIndex;
			playerComponents.erase(i);

			//update component handles
			int componentLength = playerComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[playerComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::COLLIDER:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);
			
			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(colliderComponents) + componentIndex;
			colliderComponents.erase(i);

			//update component handles
			int componentLength = colliderComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[colliderComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::HEALTH:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(healthComponents) + componentIndex;
			healthComponents.erase(i);

			//update component handles
			int componentLength = healthComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[healthComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::DAMAGE:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(damageComponents) + componentIndex;
			damageComponents.erase(i);

			//update component handles
			int componentLength = damageComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[damageComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::ENEMYCONTROLLER:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(enemyComponents) + componentIndex;
			enemyComponents.erase(i);

			//update component handles
			int componentLength = enemyComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[enemyComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::DURATION:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(durationComponents) + componentIndex;
			durationComponents.erase(i);

			//update component handles
			int componentLength = durationComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[durationComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	case Components::FILLEDBAR:
		if (obj->HasComponent(componentType))
		{
			int componentIndex = obj->GetComponentIndex(componentType);

			//remove from gameobject
			obj->RemoveComponent(componentType);

			//remove from transformComponents vector
			auto i = std::begin(filledbarComponents) + componentIndex;
			filledbarComponents.erase(i);

			//update component handles
			int componentLength = filledbarComponents.size();
			for (int i = componentIndex; i < componentLength; i++)
			{
				gameObjects[filledbarComponents[i].gameObjectId].UpdateComponentHandle(componentType, i);
			}
		}
		break;
	}
}

Component* ObjectFactory::GetComponent(GameObject* obj, Components::ComponentType componentType)
{
	// TODO: probably need to add check that it actually has the component..
	switch (componentType)
	{
	case Components::COLLIDER:
		if(obj->HasComponent(componentType))
			return &colliderComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::INPUT:
		if (obj->HasComponent(componentType))
			return &inputComponent;
		break;
	case Components::PHYSICS:
		if (obj->HasComponent(componentType))
			return &physicsComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::PLAYERCONTROLLER:
		if (obj->HasComponent(componentType))
			return &playerComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::SPRITE:
		if (obj->HasComponent(componentType))
			return &spriteComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::TRANSFORM:
		if (obj->HasComponent(componentType))
			return &transformComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::HEALTH:
		if (obj->HasComponent(componentType))
			return &healthComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::DAMAGE:
		if (obj->HasComponent(componentType))
			return &damageComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::ENEMYCONTROLLER:
		if (obj->HasComponent(componentType))
			return &enemyComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::DURATION:
		if (obj->HasComponent(componentType))
			return &durationComponents.at(obj->GetComponentIndex(componentType));
		break;
	case Components::FILLEDBAR:
		if (obj->HasComponent(componentType))
			return &filledbarComponents.at(obj->GetComponentIndex(componentType));
		break;
	default:
		printf("GetComponent Error: Invalid Component Type\n");
		return nullptr;
	}
	return nullptr;
}

GameObject* ObjectFactory::CreatePlayer(int x, int y)
{
	GameObject* player = CreateGameObject();
	Transform* playerTransform = (Transform*)AddComponent(player, Components::TRANSFORM);
	playerTransform->position.set(x, y);
	Sprite* playerSprite = (Sprite*)AddComponent(player, Components::SPRITE);
	playerSprite->spritePath.assign("./assets/sprites/hero.png");
	playerSprite->width = 32;
	playerSprite->height = 32;
	playerSprite->render_layer = 2;
	Physics* playerPhysics = (Physics*) AddComponent(player, Components::PHYSICS);
	playerPhysics->movespeed = 1.5f;
	PlayerController* playerController = (PlayerController*) AddComponent(player, Components::PLAYERCONTROLLER);
	playerController->special = -1;
	Collider* playerCollider = (Collider*)AddComponent(player, Components::COLLIDER);
	playerCollider->position = playerTransform->position;
	playerCollider->width = playerSprite->width;
	playerCollider->height = playerSprite->height;
	playerCollider->layer = CollisionLayer::PLAYER;
	Health* playerHealth = (Health*)AddComponent(player, Components::HEALTH);
	playerHealth->max_health = 100;
	playerHealth->current_health = 100;

	player->AddTag("PLAYER");

	return player;
}

GameObject* ObjectFactory::CreateProjectile(Vec2<float> position, std::string spritePath, Vec2<float> velocity, int layer)
{
	GameObject* projectile = CreateGameObject();
	Transform* transform = (Transform*)AddComponent(projectile, Components::TRANSFORM);
	transform->position = position;

	int width = 12;
	int height = 12;

	if (!spritePath.empty())
	{
		Sprite* sprite = (Sprite*)AddComponent(projectile, Components::SPRITE);
		sprite->spritePath.assign(spritePath);
		sprite->width = width;
		sprite->height = height;
		sprite->render_layer = 3;
	}

	Physics* physics = (Physics*)AddComponent(projectile, Components::PHYSICS);
	physics->velocity = velocity;
	physics->ignoreBounds = true;

	Collider* collider = (Collider*)AddComponent(projectile, Components::COLLIDER);
	collider->position = transform->position;
	collider->width = width;
	collider->height = height;
	collider->passable = true;
	collider->layer = layer;

	Duration* duration = (Duration*)AddComponent(projectile, Components::DURATION);
	duration->ttl = 5000;

	return projectile;
}

GameObject* ObjectFactory::GetPlayer()
{
	//TODO: redundant, should remove
	return GetObjectByTag("PLAYER");
}

GameObject* ObjectFactory::CreateText(std::string text, int posx, int posy)
{
	GameObject* textObj = CreateGameObject();
	Transform* textTransform = (Transform*) AddComponent(textObj, Components::TRANSFORM);
	textTransform->position.x = posx;
	textTransform->position.y = posy;
	Sprite* textSprite = (Sprite*) AddComponent(textObj, Components::SPRITE);
	textSprite->spriteText.assign(text);
	textSprite->render_layer = 5;

	return textObj;
}

GameObject* ObjectFactory::CreateButton(std::string text, int posx, int posy, int width, int height)
{
	GameObject* buttonObj = CreateText(text, posx, posy);
	Collider* buttonCollider = (Collider*) AddComponent(buttonObj, Components::COLLIDER);
	buttonCollider->position.x = posx;
	buttonCollider->position.y = posy;
	buttonCollider->width = width;
	buttonCollider->height = height;
	buttonCollider->passable = true;
	Sprite* buttonSprite = (Sprite*)GetComponent(buttonObj, Components::SPRITE);
	buttonSprite->width = width;
	buttonSprite->height = height;

	return buttonObj;
}

GameObject * ObjectFactory::GetObjectByIndex(int index)
{
	if (index >= 0 && index < gameObjects.size())
	{
		return &gameObjects.at(index);
	}
	return nullptr;
}

GameObject * ObjectFactory::GetObjectByTag(std::string tag)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject.HasTag(tag))
		{
			return &gameObject;
		}
	}
	return nullptr;
}

std::vector<GameObject*> ObjectFactory::GetObjectsByTag(std::string tag)
{
	std::vector<GameObject*> objects;

	for (auto& gameObject : gameObjects)
	{
		if (gameObject.HasTag(tag))
		{
			objects.push_back(&gameObject);
		}
	}

	return objects;
}
