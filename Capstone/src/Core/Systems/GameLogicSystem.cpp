#include "GameLogicSystem.h"
#include <time.h>
#include <stdlib.h>
#include "../Components/CollisionLayer.h"


GameLogicSystem::GameLogicSystem(ObjectFactory * objectFactoryRef) : objectFactoryRef(objectFactoryRef)
{
	int initialMods[5] = { 0,0,0,0,0 };
	currentModifiers.assign(initialMods, initialMods + 5);
	enemyScalingMultiplier = 0.1;
	currentAbility = -1;
	currentStageNumber = 0;

	bool isDemo = false;

	if (isDemo)
	{
		currentScene = new Level(objectFactoryRef, currentStageNumber, true);
	}
	else
	{
		currentScene = new Title(objectFactoryRef);
	}
}

void GameLogicSystem::Init()
{
	srand(time(NULL));
	loadScene();
}

void GameLogicSystem::Update(Uint32 dt)
{
	if(isActive())
		currentScene->Update();
}

void GameLogicSystem::HandleMessage(Message * msg)
{
	if (msg->id == "RESTART")
	{
		//objectFactoryRef->inputComponent.events.clear();
		loadScene();
		printf("Restart message received by gamelogicsystem\n");
	}
	else if (msg->id == "LOAD LEVEL")
	{
		currentScene->Unload();
		delete currentScene;
		currentScene = new Level(objectFactoryRef, ++currentStageNumber, false);
		currentScene->Load();
		applyModifiers(currentModifiers);
		// if health was modified, update displayed health (pretty hacky)
		if (currentModifiers[4] == 1)
		{
			Message* msg = new Message();
			msg->id.assign("PLAYER DAMAGED");
			Engine::BroadcastMessage(msg);
		}
	}
	else if (msg->id == "LOAD TITLE")
	{
		currentStageNumber = 0;
		currentScene->Unload();
		delete currentScene;
		currentScene = new Title(objectFactoryRef);
		currentScene->Load();
	}
	else if (msg->id == "LOAD MODS")
	{
		currentScene->Unload();
		delete currentScene;
		float totalEnemyMulti = enemyScalingMultiplier * currentStageNumber;
		currentScene = new ModDisplay(objectFactoryRef, totalEnemyMulti);
		currentScene->Load();
	}
	else if (msg->id == "UPDATE MODS")
	{
		int* mods = static_cast<int*>(msg->data);
		currentModifiers.assign(mods, mods + 5);
	}
	else if (msg->id == "SELECT ABILITY")
	{
		currentScene->Unload();
		delete currentScene;
		currentScene = new AbilitySelect(objectFactoryRef);
		currentScene->Load();
	}
	else if (msg->id == "UPDATE ABILITY")
	{
		currentAbility = *static_cast<int*>(msg->data);
	}
	else
	{
		currentScene->HandleMessage(msg);
	}
}

GameLogicSystem::~GameLogicSystem()
{
}

void GameLogicSystem::loadScene()
{
	if (currentScene != nullptr)
	{
		currentScene->Unload();
		//delete currentScene;
		currentScene->Load();
	}
}

// mods[] damage, attack rate, cooldown, movespeed, health
void GameLogicSystem::applyModifiers(std::vector<int> mods)
{
	std::vector<GameObject*> players = objectFactoryRef->GetObjectsByTag("PLAYER");
	std::vector<GameObject*> enemies = objectFactoryRef->GetObjectsByTag("ENEMY");

	// currently applying same mods to player and enemies, but could change
	float damageMod = 1.5;
	float attackRateMod = 0.5;
	float cooldownMod = 0.5;
	float movespeedMod = 1.5;
	float healthMod = 2.f;

	for (auto player : players)
	{	
		PlayerController* playerController = (PlayerController*)objectFactoryRef->GetComponent(player, Components::PLAYERCONTROLLER);
		if (playerController)
		{
			// damage
			if (mods[0] == 1)
			{
				playerController->damage *= damageMod;
			}

			// attack rate

			// cooldown
			if (mods[2] == 1)
			{
				for (auto &cooldown : playerController->special_cooldown)
				{
					cooldown *= cooldownMod;
				}

				for (auto &specialMod : playerController->special_modifier)
				{
					specialMod *= (1 + cooldownMod);
				}
			}

			// movespeed
			if (mods[3] == 1)
			{
				Physics* playerPhysics = (Physics*)objectFactoryRef->GetComponent(player, Components::PHYSICS);
				if (playerPhysics)
				{
					playerPhysics->movespeed *= movespeedMod;
				}
			}

			// health
			if (mods[4] == 1)
			{
				Health* playerHealth = (Health*)objectFactoryRef->GetComponent(player, Components::HEALTH);
				if (playerHealth)
				{
					playerHealth->max_health *= healthMod;
					playerHealth->current_health *= healthMod;
				}
			}

			playerController->special = currentAbility;
		}
	}

	for (auto enemy : enemies)
	{
		EnemyController* enemyController = (EnemyController*)objectFactoryRef->GetComponent(enemy, Components::ENEMYCONTROLLER);
		if (enemyController)
		{
			// stage scaling
			enemyController->attackDamage *= (1 + (enemyScalingMultiplier * (currentStageNumber - 1)));

			Health* enemyhealth = (Health*)objectFactoryRef->GetComponent(enemy, Components::HEALTH);
			if (enemyhealth)
			{
				enemyhealth->max_health *= (1 + (enemyScalingMultiplier * (currentStageNumber - 1)));
				enemyhealth->current_health *= (1 + (enemyScalingMultiplier * (currentStageNumber - 1)));
			}


			// modifier scaling

			// damage
			if (mods[0] == 1)
			{
				enemyController->attackDamage *= damageMod;
			}

			// attack rate
			if (mods[1] == 1)
			{
				enemyController->attackCooldown *= attackRateMod;
			}

			// cooldown

			// movespeed
			if (mods[3] == 1)
			{
				Physics* enemyPhysics = (Physics*)objectFactoryRef->GetComponent(enemy, Components::PHYSICS);
				if (enemyPhysics)
				{
					enemyPhysics->movespeed *= movespeedMod;
				}
			}

			// health
			if (mods[4] == 1)
			{
				if (enemyhealth)
				{
					enemyhealth->max_health *= healthMod;
					enemyhealth->current_health *= healthMod;
				}
			}
		}
	}
}