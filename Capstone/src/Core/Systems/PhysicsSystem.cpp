#include "PhysicsSystem.h"
#include "../Components/CollisionLayer.h"

PhysicsSystem::PhysicsSystem(ObjectFactory* objectFactory)
{
	objectFactoryRef = objectFactory;
	gameObjectsRef = &objectFactoryRef->gameObjects;
	physicsComponents = &objectFactoryRef->physicsComponents;
	transformComponents = &objectFactoryRef->transformComponents;
	colliderComponents = &objectFactoryRef->colliderComponents;
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		// TODO: update all the component gets with the later added helper function

		//reset collisions
		for (auto& collider : *colliderComponents)
		{
			collider.collisionGameObjectIds.clear();
			// probably dont even need this bool anymore, can just check if vector is empty
			collider.collision = false;
			collider.hover = false;
			collider.clicked = false;
		}

		// update object positions
		for (auto& movementComp : *physicsComponents)
		{
			if (movementComp.active)
			{
				int transformIndex = gameObjectsRef->at(movementComp.gameObjectId).GetComponentIndex(Components::TRANSFORM);
				if (transformIndex != -1)
				{
					Transform* transform = &transformComponents->at(transformIndex);
					transform->position.x += movementComp.velocity.x;
					transform->position.y += movementComp.velocity.y;
					movementComp.velocity += movementComp.acceleration;

					GameObject object = gameObjectsRef->at(transform->gameObjectId);
					Collider* collider = (Collider*)objectFactoryRef->GetComponent(&object, Components::COLLIDER);
					if (collider)
					{
						collider->position.x += movementComp.velocity.x;
						collider->position.y += movementComp.velocity.y;
					}

					// TODO: this probably shouldn't be here at all, and instead be added below at collision checking
					// temp: check screen bounds, probably cleaner to add a collider at edge of screen, so i can also destroy projectiles
					if (!movementComp.ignoreBounds)
					{
						if (transform->position.x < 0)
						{
							transform->position.x = 0;
							if (collider)
								collider->position.x = 0;
						}
						// temp, will go off screen on bottom and right sides
						else if (transform->position.x + Settings::TILE_SIZE > Settings::SCREEN_WIDTH)
						{
							transform->position.x = Settings::SCREEN_WIDTH - Settings::TILE_SIZE;
							if (collider)
								collider->position.x = Settings::SCREEN_WIDTH - Settings::TILE_SIZE;
						}
						if (transform->position.y < 0)
						{
							transform->position.y = 0;
							if (collider)
								collider->position.y = 0;
						}
						// temp, same error as above
						else if (transform->position.y + Settings::TILE_SIZE > Settings::SCREEN_HEIGHT)
						{
							transform->position.y = Settings::SCREEN_HEIGHT - Settings::TILE_SIZE;
							if (collider)
								collider->position.y = Settings::SCREEN_HEIGHT - Settings::TILE_SIZE;
						}
					}
				}
			}
		}

		//check for collisions

		Vec2<float> mousePos = Engine::GetRelMousePos();

		bool clicked = false;

		for (auto event : objectFactoryRef->inputComponent.events)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				// TODO: add specific buttons
				clicked = true;
				break;
			}
		}

		int numberOfColliders = colliderComponents->size();
		for (int i = 0; i < numberOfColliders; i++)
		{
			// TODO: this should all be updated with new helper functions
			Collider* c1 = &colliderComponents->at(i);
			Physics* c1Phys = nullptr;
			if (gameObjectsRef->at(c1->gameObjectId).HasComponent(Components::PHYSICS))
			{
				c1Phys = &physicsComponents->at(gameObjectsRef->at(c1->gameObjectId).GetComponentIndex(Components::PHYSICS));
			}
			Transform* c1Trans = &transformComponents->at(gameObjectsRef->at(c1->gameObjectId).GetComponentIndex(Components::TRANSFORM));

			// check for collision with mouse
			if (mousePos.x <= c1->position.x + c1->width &&
				mousePos.x >= c1->position.x &&
				mousePos.y <= c1->position.y + c1->height &&
				mousePos.y >= c1->position.y)
			{
				c1->hover = true;
				if (clicked)
				{
					c1->clicked = true;
					//printf("Object %d clicked\n", c1->gameObjectId);
				}
			}

			for (int j = i + 1; j < numberOfColliders; j++)
			{
				Collider* c2 = &colliderComponents->at(j);

				// collisions only happen within same layer
				if (c1->layer == c2->layer || c1->layer == CollisionLayer::ALL || c2->layer == CollisionLayer::ALL)
				{
					if (c1->position.x < c2->position.x + c2->width &&
						c1->position.x + c1->width > c2->position.x &&
						c1->position.y < c2->position.y + c2->height &&
						c1->position.y + c1->height > c2->position.y)
					{
						c1->collision = true;
						c1->collisionGameObjectIds.push_back(c2->gameObjectId);
						c2->collision = true;
						c2->collisionGameObjectIds.push_back(c1->gameObjectId);

						//TODO: temp? handle this elsewhere? maybe update with GetComponent function
						Physics* c2Phys = nullptr;
						if (gameObjectsRef->at(c2->gameObjectId).HasComponent(Components::PHYSICS))
						{
							c2Phys = &physicsComponents->at(gameObjectsRef->at(c2->gameObjectId).GetComponentIndex(Components::PHYSICS));
						}

						if (!c1->passable && !c2->passable)
						{
							// handle c1
							if (c1Phys)
							{
								c1Trans->position.x -= (c1Phys->velocity.x + c1Phys->acceleration.x);
								c1Trans->position.y -= (c1Phys->velocity.y + c1Phys->acceleration.y);
								c1->position.x -= (c1Phys->velocity.x + c1Phys->acceleration.x);
								c1->position.y -= (c1Phys->velocity.y + c1Phys->acceleration.y);
							}

							// handle c2
							if (c2Phys)
							{
								Transform* c2Trans = &transformComponents->at(gameObjectsRef->at(c2->gameObjectId).GetComponentIndex(Components::TRANSFORM));
								c2Trans->position.x -= (c2Phys->velocity.x + c2Phys->acceleration.x);
								c2Trans->position.y -= (c2Phys->velocity.y + c2Phys->acceleration.y);
								c2->position.x -= (c2Phys->velocity.x + c2Phys->acceleration.x);
								c2->position.y -= (c2Phys->velocity.y + c2Phys->acceleration.y);
							}
						}
					}
				}
			}
		}
	}
}

void PhysicsSystem::HandleMessage(Message * msg)
{
	if (msg->id == "QUIT")
	{

	}
}
