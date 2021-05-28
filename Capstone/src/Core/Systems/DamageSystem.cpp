#include "DamageSystem.h"

DamageSystem::DamageSystem(ObjectFactory * objectFactory)
{
	objectFactoryRef = objectFactory;
	damageComponents = &objectFactory->damageComponents;
	healthComponents = &objectFactoryRef->healthComponents;
	colliderComponents = &objectFactoryRef->colliderComponents;
}

void DamageSystem::Init()
{
}

void DamageSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		for (int i = 0; i < damageComponents->size(); i++)
		{
			Damage* damageComponent = &damageComponents->at(i);
			GameObject* obj = &objectFactoryRef->gameObjects.at(damageComponent->gameObjectId);
			if (obj->HasComponent(Components::COLLIDER))
			{
				Collider* col = (Collider*)objectFactoryRef->GetComponent(obj, Components::COLLIDER);
				std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
				if (col->collision && (currentTime - damageComponent->lastTick >= std::chrono::milliseconds(damageComponent->frequency)))
				{
					bool destroy = false;
					for (auto objectId : col->collisionGameObjectIds)
					{
						GameObject* obj2 = objectFactoryRef->GetObjectByIndex(objectId);

						//if ((currentTime - damageComponent->lastTick >= std::chrono::milliseconds(damageComponent->frequency)) && obj2 && obj2->HasComponent(Components::HEALTH))
						if (obj2 && obj2->HasComponent(Components::HEALTH))
						{
							Health* health = (Health*)objectFactoryRef->GetComponent(obj2, Components::HEALTH);
							health->current_health -= damageComponent->value;
							damageComponent->lastTick = currentTime;

							//printf("Damage dealt: %d\n", damageComponent->value);

							// bad
							if (obj2->HasComponent(Components::PLAYERCONTROLLER))
							{
								Message* msg = new Message();
								msg->id.assign("PLAYER DAMAGED");
								Engine::BroadcastMessage(msg);
							}

							destroy = true;
						}
					}
					if (destroy && damageComponent->frequency == 0)
					{
						objectFactoryRef->DestroyGameObject(obj);
						i--;
					}
				}
			}
		}
	}
}

void DamageSystem::HandleMessage(Message * msg)
{
}
