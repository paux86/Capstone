#include "Level.h"

Level::Level(ObjectFactory * objectFactory, int stageNum, bool isDemo) : Scene(objectFactory)
{
	stageNumber = stageNum;
	demo = isDemo;
}

void Level::Load()
{
	if (demo)
	{
		//player
		int player_xPos =300;
		int player_yPos = 200;

		GameObject* player = objectFactoryRef->CreateGameObject();
		Transform* playerTransform = (Transform*)objectFactoryRef->AddComponent(player, Components::TRANSFORM);
		playerTransform->position.set(player_xPos, player_yPos);
		Sprite* playerSprite = (Sprite*)objectFactoryRef->AddComponent(player, Components::SPRITE);
		playerSprite->spritePath.assign("./assets/sprites/hero.png");
		Physics* playerPhysics = (Physics*)objectFactoryRef->AddComponent(player, Components::PHYSICS);
		playerPhysics->movespeed = 1.5f;
		//playerPhysics->velocity.x = playerPhysics->movespeed;
		PlayerController* playerController = (PlayerController*)objectFactoryRef->AddComponent(player, Components::PLAYERCONTROLLER);

		










		
		GameObject* player2 = objectFactoryRef->CreateGameObject();
		Transform* player2Transform = (Transform*)objectFactoryRef->AddComponent(player2, Components::TRANSFORM);
		player2Transform->position.set(player_xPos + 100, player_yPos + 50);
		Sprite* player2Sprite = (Sprite*)objectFactoryRef->AddComponent(player2, Components::SPRITE);
		player2Sprite->spritePath.assign("./assets/sprites/hero.png");
		Physics* player2Physics = (Physics*)objectFactoryRef->AddComponent(player2, Components::PHYSICS);
		player2Physics->movespeed = 1.5f;
		PlayerController* player2Controller = (PlayerController*)objectFactoryRef->AddComponent(player2, Components::PLAYERCONTROLLER);
		











		std::string bg_paths[] = { "./assets/sprites/bricks.png", "./assets/sprites/bricks_yellow.png", "./assets/sprites/bricks_blue.png" };
		int bg_selection_index = 0;
		float tile_width = 32.f;
		for (float x = 0.f; x < Settings::SCREEN_WIDTH; x += tile_width)
		{
			for (float y = 0.f; y < Settings::SCREEN_HEIGHT; y += tile_width)
			{
				GameObject* tile = objectFactoryRef->CreateGameObject();
				Transform* tileTransform = (Transform*)objectFactoryRef->AddComponent(tile, Components::TRANSFORM);
				tileTransform->position = Vec2<float>(x, y);
				Sprite* tileSprite = (Sprite*)objectFactoryRef->AddComponent(tile, Components::SPRITE);
				tileSprite->render_layer = 0;
				//tileSprite->spritePath.assign("./assets/sprites/garbage_tile.png");
				tileSprite->spritePath.assign(bg_paths[bg_selection_index]);
				tileSprite->width = tile_width;
				tileSprite->height = tile_width;
			}
		}
	}
	else
	{
		objectFactoryRef->CreateText("Stage " + std::to_string(stageNumber), Settings::SCREEN_WIDTH / 2 - 50, 20);

		//player
		int player_xPos = 10;
		int player_yPos = 50;
		int enemySpawnPosBuffer = 80;
		GameObject* player = objectFactoryRef->CreatePlayer(player_xPos, player_yPos);

		GameObject* playerHealthBar = objectFactoryRef->CreateGameObject();
		Transform* healthBarTransform = (Transform*)objectFactoryRef->AddComponent(playerHealthBar, Components::TRANSFORM);
		healthBarTransform->position.x = 10;
		healthBarTransform->position.y = 15;
		objectFactoryRef->AddComponent(playerHealthBar, Components::FILLEDBAR);
		playerHealthBar->AddTag("PlayerHealthBar");

		int extraEnemies = rand() % 9;
		int numEnemies = 12 + extraEnemies;
		int numMeatballs = 12 + rand() % (extraEnemies + 1);
		int numDogs = numEnemies - numMeatballs;
		enemiesRemaining = numEnemies;
		printf("Spawned %d Meatballs, %d Blue dogs, %d total\n", numMeatballs, numDogs, numEnemies);

		// spawn meatballs
		for (int i = 0; i < numMeatballs; i++)
		{
			int x = (rand() % (Settings::SCREEN_WIDTH - (player_xPos + enemySpawnPosBuffer + Settings::TILE_SIZE))) + (player_xPos + enemySpawnPosBuffer + Settings::TILE_SIZE);
			int y = (rand() % (Settings::SCREEN_HEIGHT - (player_yPos + enemySpawnPosBuffer + Settings::TILE_SIZE))) + (player_yPos + enemySpawnPosBuffer + Settings::TILE_SIZE);

			GameObject* enemy = objectFactoryRef->CreatePlayer(x, y);
			objectFactoryRef->RemoveComponent(enemy, Components::PLAYERCONTROLLER);
			EnemyController* enemyController = (EnemyController*)objectFactoryRef->AddComponent(enemy, Components::ENEMYCONTROLLER);
			enemyController->aggroRange = 500.f;
			enemyController->attackRange = 300.f;
			enemyController->attackDamage = 50;
			Collider* enemyCollider = (Collider*)objectFactoryRef->GetComponent(enemy, Components::COLLIDER);
			enemyCollider->layer = CollisionLayer::ENEMY;
			enemyCollider->passable = true;
			Sprite* enemySprite = (Sprite*)objectFactoryRef->GetComponent(enemy, Components::SPRITE);
			enemySprite->spritePath.assign("./assets/sprites/meatball.png");

			enemy->RemoveTag("PLAYER");
			enemy->AddTag("ENEMY");
		}

		// spawn dogs
		for (int i = 0; i < numDogs; i++)
		{
			int x = (rand() % (Settings::SCREEN_WIDTH - (player_xPos + enemySpawnPosBuffer + Settings::TILE_SIZE))) + (player_xPos + enemySpawnPosBuffer + Settings::TILE_SIZE);
			int y = (rand() % (Settings::SCREEN_HEIGHT - (player_yPos + enemySpawnPosBuffer + Settings::TILE_SIZE))) + (player_yPos + enemySpawnPosBuffer + Settings::TILE_SIZE);

			GameObject* enemy = objectFactoryRef->CreatePlayer(x, y);
			objectFactoryRef->RemoveComponent(enemy, Components::PLAYERCONTROLLER);
			EnemyController* enemyController = (EnemyController*)objectFactoryRef->AddComponent(enemy, Components::ENEMYCONTROLLER);
			enemyController->aggroRange = 1500.f;
			enemyController->attackRange = 32.f;
			enemyController->attackDamage = 100;
			enemyController->movementSpeed = 1.2;
			enemyController->projectileSpeed = 0.f;
			enemyController->projectileDuration = 500;
			enemyController->projectileSpritePath.clear();
			Collider* enemyCollider = (Collider*)objectFactoryRef->GetComponent(enemy, Components::COLLIDER);
			enemyCollider->layer = CollisionLayer::ENEMY;
			enemyCollider->passable = true;
			Sprite* enemySprite = (Sprite*)objectFactoryRef->GetComponent(enemy, Components::SPRITE);
			enemySprite->spritePath.assign("./assets/sprites/blue_dog.png");
			Health* enemyHealth = (Health*)objectFactoryRef->GetComponent(enemy, Components::HEALTH);
			enemyHealth->current_health = enemyHealth->max_health = 300;

			enemy->RemoveTag("PLAYER");
			enemy->AddTag("ENEMY");
		}

		//temp background (shouldnt be loading same asset multiple times)
		std::string bg_paths[] = { "./assets/sprites/bricks.png", "./assets/sprites/bricks_yellow.png", "./assets/sprites/bricks_blue.png" };
		int bg_selection_index = rand() % 3;
		float tile_width = 32.f;
		for (float x = 0.f; x < Settings::SCREEN_WIDTH; x += tile_width)
		{
			for (float y = 0.f; y < Settings::SCREEN_HEIGHT; y += tile_width)
			{
				GameObject* tile = objectFactoryRef->CreateGameObject();
				Transform* tileTransform = (Transform*)objectFactoryRef->AddComponent(tile, Components::TRANSFORM);
				tileTransform->position = Vec2<float>(x, y);
				Sprite* tileSprite = (Sprite*)objectFactoryRef->AddComponent(tile, Components::SPRITE);
				tileSprite->render_layer = 0;
				//tileSprite->spritePath.assign("./assets/sprites/garbage_tile.png");
				tileSprite->spritePath.assign(bg_paths[bg_selection_index]);
				tileSprite->width = tile_width;
				tileSprite->height = tile_width;
			}
		}
	}
}

void Level::Update()
{
	if (!demo)
	{
		std::vector<GameObject*> enemies = objectFactoryRef->GetObjectsByTag("ENEMY");
		if (enemies.size() <= 0)
		{
			// TODO: temp? rather than delete, just pause systems
			//objectFactoryRef->DestroyAllGameObjects();
			GameObject* winText = objectFactoryRef->CreateText("Enemies defeated", Settings::SCREEN_WIDTH / 2 - 100, 185);
			Duration* textDuration = (Duration*)objectFactoryRef->AddComponent(winText, Components::DURATION);
			textDuration->ttl = 3000;
			textDuration->msgString.assign("LOAD MODS");
		}
		else if (objectFactoryRef->GetPlayer() == nullptr)
		{
			// TODO: temp? rather than delete, just pause systems
			//objectFactoryRef->DestroyAllGameObjects();
			GameObject* loseText = objectFactoryRef->CreateText("You died.", Settings::SCREEN_WIDTH / 2 - 85, 185);
			Duration* textDuration = (Duration*)objectFactoryRef->AddComponent(loseText, Components::DURATION);
			textDuration->ttl = 3000;
			textDuration->msgString.assign("LOAD TITLE");
		}
	}
}

void Level::HandleMessage(Message* msg)
{
	if (!demo)
	{
		if (msg->id == "ENEMYDIED")
		{
			score++;
			GameObject* scoreObj = objectFactoryRef->GetObjectByTag("ScoreText");
			if (scoreObj != nullptr)
			{
				Transform* scoreObjTransform = (Transform*)objectFactoryRef->GetComponent(scoreObj, Components::TRANSFORM);
				int posx = scoreObjTransform->position.x;
				int posy = scoreObjTransform->position.y;
				objectFactoryRef->DestroyGameObject(scoreObj);
				GameObject* updatedScoreObj = objectFactoryRef->CreateText("Score: " + std::to_string(score), posx, posy);
				updatedScoreObj->AddTag("ScoreText");
			}

			enemiesRemaining--;
			GameObject* enemyCounterObj = objectFactoryRef->GetObjectByTag("EnemyCounter");
			if (enemyCounterObj != nullptr)
			{
				Transform* enemyCounterObjTransform = (Transform*)objectFactoryRef->GetComponent(enemyCounterObj, Components::TRANSFORM);
				int posx = enemyCounterObjTransform->position.x;
				int posy = enemyCounterObjTransform->position.y;
				objectFactoryRef->DestroyGameObject(enemyCounterObj);
				GameObject* updatedEnemyCounter = objectFactoryRef->CreateText("Enemies Remaining: " + std::to_string(enemiesRemaining), posx, posy);
				updatedEnemyCounter->AddTag("EnemyCounter");
			}
		}
		if (msg->id == "PLAYER DAMAGED")
		{
			//update health text
			GameObject* healthBar = objectFactoryRef->GetObjectByTag("PlayerHealthBar");
			if (healthBar)
			{
				FilledBar* bar = (FilledBar*)objectFactoryRef->GetComponent(healthBar, Components::FILLEDBAR);
				if (bar)
				{
					float healthPercent = 0.f;
					GameObject* player = objectFactoryRef->GetPlayer();
					if (player)
					{
						Health* playerHealth = (Health*)objectFactoryRef->GetComponent(player, Components::HEALTH);
						if (playerHealth)
						{
							healthPercent = (float)playerHealth->current_health / playerHealth->max_health;
						}
					}
					bar->fillPercent = healthPercent;
				}
			}
		}
	}
}