#include "HealthSystem.h"

HealthSystem::HealthSystem(ObjectFactory* objectFactory)
{
	objectFactoryRef = objectFactory;
	healthComponents = &objectFactoryRef->healthComponents;
}

void HealthSystem::Init()
{
}

void HealthSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		for (int i = 0; i < healthComponents->size();)
		{
			Health* health = &healthComponents->at(i);
			if (health->current_health <= 0)
			{
				health->current_health = 0;
				//printf("Rip object %d\n", health->gameObjectId);
				GameObject* obj = &objectFactoryRef->gameObjects.at(health->gameObjectId);
				// TODO: temp, for incrementing score. should update message system
				if (obj->HasComponent(Components::ENEMYCONTROLLER))
				{
					Message* enemyDiedMessage = new Message();
					enemyDiedMessage->id.assign("ENEMYDIED");
					Engine::BroadcastMessage(enemyDiedMessage);
				}
				objectFactoryRef->DestroyGameObject(obj);
			}
			else
				i++;
		}
	}
}

void HealthSystem::HandleMessage(Message* msg)
{
}
