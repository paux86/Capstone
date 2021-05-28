#include "PlayerControllerSystem.h"
#include "../Components/CollisionLayer.h"
#include <chrono>

PlayerControllerSystem::PlayerControllerSystem(ObjectFactory* objectFactory) : objectFactoryRef(objectFactory)
{

}

PlayerControllerSystem::~PlayerControllerSystem()
{
}

void PlayerControllerSystem::Init()
{
}

void PlayerControllerSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		for (auto& playerComponent : objectFactoryRef->playerComponents)
		{
			GameObject* player = &objectFactoryRef->gameObjects.at(playerComponent.gameObjectId);
			Transform* playerTransform = (Transform*)objectFactoryRef->GetComponent(player, Components::TRANSFORM);

			if (player->HasComponent(Components::PHYSICS))
			{
				Physics* playerPhysics = &objectFactoryRef->physicsComponents.at(player->GetComponentIndex(Components::PHYSICS));
				float movespeed = playerPhysics->movespeed;

				for (auto event : objectFactoryRef->inputComponent.events)
				{
					if (event.type == SDL_KEYDOWN)
					{
						switch (event.key.keysym.sym)
						{
							// movement
						case SDLK_w:
							if (playerPhysics->velocity.y > -movespeed)
								playerPhysics->velocity.y -= movespeed;
							break;
						case SDLK_s:
							if (playerPhysics->velocity.y < movespeed)
								playerPhysics->velocity.y += movespeed;
							break;
						case SDLK_a:
							if (playerPhysics->velocity.x > -movespeed)
								playerPhysics->velocity.x -= movespeed;
							break;
						case SDLK_d:
							if (playerPhysics->velocity.x < movespeed)
								playerPhysics->velocity.x += movespeed;
							break;
							// shield/barrier
						case SDLK_f:
						{
							if (playerComponent.special == -1)
								createShield(playerComponent, playerTransform);
						}
						break;
						// HoT/DoT pool
						case SDLK_r:
						{
							if (playerComponent.special == -1)
								createCircle(player, playerComponent, playerTransform);
						}
						break;
						// load to title
						case SDLK_F1:
						{
							Message* msg = new Message();
							msg->id.assign("LOAD TITLE");
							Engine::BroadcastMessage(msg);
						}
						break;
						case SDLK_ESCAPE:
						{
							Message* msg = new Message();
							msg->id.assign("QUIT");
							Engine::BroadcastMessage(msg);
						}
						break;
						}
					}
					else if (event.type == SDL_KEYUP)
					{
						switch (event.key.keysym.sym)
						{
						case SDLK_w:
							playerPhysics->velocity.y += movespeed;
							break;
						case SDLK_s:
							playerPhysics->velocity.y -= movespeed;
							break;
						case SDLK_a:
							playerPhysics->velocity.x += movespeed;
							break;
						case SDLK_d:
							playerPhysics->velocity.x -= movespeed;
							break;
						}
					}
					else if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						//get mouse pos
						Vec2<float> mousePos = Engine::GetRelMousePos();

						switch (event.button.button)
						{
						case SDL_BUTTON_LEFT:
						{
							GameObject* proj = objectFactoryRef->CreateProjectile(playerTransform->position, "./assets/sprites/bullet_blue.png", (mousePos - playerTransform->position).normalize() * 3.f, CollisionLayer::ENEMY);
							Damage* projDamage = (Damage*)objectFactoryRef->AddComponent(proj, Components::DAMAGE);
							projDamage->value = playerComponent.damage;
						}
						break;
						case SDL_BUTTON_RIGHT:
						{
							if (playerComponent.special == -1)
								dodge(player, playerComponent, playerPhysics, playerTransform);
							else
							{
								switch (playerComponent.special)
								{
								case 0:
									createShield(playerComponent, playerTransform);
									break;
								case 1:
									createCircle(player, playerComponent, playerTransform);
									break;
								case 2:
									dodge(player, playerComponent, playerPhysics, playerTransform);
									break;
								}
							}
						}
						break;
						}
					}
				}
			}
		}
	}
}

void PlayerControllerSystem::HandleMessage(Message * msg)
{

}


void PlayerControllerSystem::createShield(PlayerController& playerComponent, Transform* playerTransform) 
{
	// shouldnt hardcode this
	int special = 0;

	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (currentTime - playerComponent.special_last_used >= std::chrono::milliseconds(playerComponent.special_cooldown[special]))
	{
		GameObject* shieldObj = objectFactoryRef->CreateGameObject();
		Transform* shieldTransform = (Transform*)objectFactoryRef->AddComponent(shieldObj, Components::TRANSFORM);
		shieldTransform->position = playerTransform->position;
		Sprite* shieldSprite = (Sprite*)objectFactoryRef->AddComponent(shieldObj, Components::SPRITE);
		shieldSprite->spritePath.assign("./assets/sprites/shield_with_cross.png");
		shieldSprite->render_layer = 3;
		Duration* shieldDuration = (Duration*)objectFactoryRef->AddComponent(shieldObj, Components::DURATION);
		shieldDuration->ttl = playerComponent.special_modifier[special];
		Collider* shieldCollider = (Collider*)objectFactoryRef->AddComponent(shieldObj, Components::COLLIDER);
		shieldCollider->position = playerTransform->position;
		shieldCollider->layer = CollisionLayer::ALL;
		shieldCollider->passable = true;
		Health* shieldHealth = (Health*)objectFactoryRef->AddComponent(shieldObj, Components::HEALTH);
		shieldHealth->current_health = shieldHealth->max_health = 100000;

		playerComponent.special_last_used = currentTime;
	}
}

void PlayerControllerSystem::createCircle(GameObject* player, PlayerController& playerComponent, Transform* playerTransform)
{
	// shouldnt hardcode this
	int special = 1;

	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (currentTime - playerComponent.special_last_used >= std::chrono::milliseconds(playerComponent.special_cooldown[special]))
	{
		// HoT - 25% of max health per second
		GameObject* healObj = objectFactoryRef->CreateGameObject();
		Transform* healTransform = (Transform*)objectFactoryRef->AddComponent(healObj, Components::TRANSFORM);
		healTransform->position.x = playerTransform->position.x - 32.f;
		healTransform->position.y = playerTransform->position.y - 32.f;
		Duration* healDuration = (Duration*)objectFactoryRef->AddComponent(healObj, Components::DURATION);
		healDuration->ttl = playerComponent.special_modifier[special];
		Collider* healCollider = (Collider*)objectFactoryRef->AddComponent(healObj, Components::COLLIDER);
		healCollider->position = healTransform->position;
		healCollider->width = 96;
		healCollider->height = 96;
		healCollider->layer = CollisionLayer::PLAYER;
		healCollider->passable = true;

		Health* playerHealth = (Health*)objectFactoryRef->GetComponent(player, Components::HEALTH);
		int healValue = 50;
		if (playerHealth)
			healValue = playerHealth->max_health * 0.25;
		Damage* healDamage = (Damage*)objectFactoryRef->AddComponent(healObj, Components::DAMAGE);
		healDamage->value = -healValue;
		healDamage->frequency = 1000;

		// DoT - 50% of proj damage per second
		GameObject* damageObj = objectFactoryRef->CreateGameObject();
		Transform* damageTransform = (Transform*)objectFactoryRef->AddComponent(damageObj, Components::TRANSFORM);
		damageTransform->position = healTransform->position;
		Sprite* shieldSprite = (Sprite*)objectFactoryRef->AddComponent(damageObj, Components::SPRITE);
		shieldSprite->spritePath.assign("./assets/sprites/spell_circle_green.png");
		shieldSprite->width = 96;
		shieldSprite->height = 96;
		Duration* damageDuration = (Duration*)objectFactoryRef->AddComponent(damageObj, Components::DURATION);
		damageDuration->ttl = playerComponent.special_modifier[special];
		Collider* damageCollider = (Collider*)objectFactoryRef->AddComponent(damageObj, Components::COLLIDER);
		damageCollider->position = damageTransform->position;
		damageCollider->width = 96;
		damageCollider->height = 96;
		damageCollider->layer = CollisionLayer::ENEMY;
		damageCollider->passable = true;
		Damage* damage = (Damage*)objectFactoryRef->AddComponent(damageObj, Components::DAMAGE);
		damage->value = playerComponent.damage * 0.5;
		damage->frequency = 1000;

		playerComponent.special_last_used = currentTime;
	}
}

void PlayerControllerSystem::dodge(GameObject* player, PlayerController& playerComponent, Physics* playerPhysics, Transform* playerTransform)
{
	// shouldnt hardcode this
	int special = 2;

	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (currentTime - playerComponent.special_last_used >= std::chrono::milliseconds(playerComponent.special_cooldown[special]))
	{
		// should create a helper function for moving transform and collider at the same time
		Vec2<float> dodge = playerPhysics->velocity * (float)playerComponent.special_modifier[special];
		playerTransform->position += dodge;

		Collider* playerCollider = (Collider*)objectFactoryRef->GetComponent(player, Components::COLLIDER);
		playerCollider->position += dodge;

		playerComponent.special_last_used = currentTime;
	}
}

void PlayerControllerSystem::setActive(bool is_active)
{
	if (!isActive() && is_active)
	{
		for (auto& playerComponent : objectFactoryRef->playerComponents)
		{
			GameObject* player = objectFactoryRef->GetObjectByIndex(playerComponent.gameObjectId);
			Physics* playerPhysics = (Physics*)objectFactoryRef->GetComponent(player, Components::PHYSICS);
			playerPhysics->velocity.x = 0.f;
			playerPhysics->velocity.y = 0.f;
		}
	}
	System::setActive(is_active);
}