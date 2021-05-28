#include "EnemyControllerSystem.h"
#include "../Components/CollisionLayer.h"
#include <chrono>

EnemyControllerSystem::EnemyControllerSystem(ObjectFactory * objectFactory)
{
	objectFactoryRef = objectFactory;
	enemyControllers = &objectFactoryRef->enemyComponents;
}

void EnemyControllerSystem::Init()
{
}

void EnemyControllerSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		GameObject* player = objectFactoryRef->GetPlayer();
		if (player != nullptr)
		{
			Transform* playerTransform = (Transform*)objectFactoryRef->GetComponent(player, Components::TRANSFORM);

			for (auto& enemyController : *enemyControllers)
			{
				GameObject* enemy = &objectFactoryRef->gameObjects.at(enemyController.gameObjectId);

				if (enemy->HasComponent(Components::PHYSICS))
				{
					Transform* enemyTransform = (Transform*)objectFactoryRef->GetComponent(enemy, Components::TRANSFORM);
					Physics* enemyPhysics = (Physics*)objectFactoryRef->GetComponent(enemy, Components::PHYSICS);

					// move towards player if within aggro range but not attack range
					float distanceToPlayer = (playerTransform->position - enemyTransform->position).length();
					if (distanceToPlayer < enemyController.aggroRange && distanceToPlayer > enemyController.attackRange)
					{
						enemyPhysics->velocity = (playerTransform->position - enemyTransform->position).normalize() * enemyController.movementSpeed;
					}

					// attack if within attack range
					if (std::chrono::steady_clock::now() - enemyController.lastAttackTime >= std::chrono::milliseconds(enemyController.attackCooldown) && distanceToPlayer < enemyController.attackRange)
					{
						//ATTACK
						GameObject* proj = objectFactoryRef->CreateProjectile(enemyTransform->position, enemyController.projectileSpritePath, (playerTransform->position - enemyTransform->position).normalize() * enemyController.projectileSpeed, CollisionLayer::PLAYER);
						Damage* projDamage = (Damage*)objectFactoryRef->AddComponent(proj, Components::DAMAGE);
						projDamage->value = enemyController.attackDamage;
						if (enemyController.projectileDuration > 0)
						{
							Duration* projDuration = (Duration*)objectFactoryRef->GetComponent(proj, Components::DURATION);
							projDuration->ttl = enemyController.projectileDuration;
						}
						enemyController.lastAttackTime = std::chrono::steady_clock::now();
					}
				}
			}
		}
	}
}

void EnemyControllerSystem::HandleMessage(Message * msg)
{
}
