#include "Game.h"

Game::Game()
{
	objectFactory = &engine.objectFactory;
}

Game::~Game()
{
}

void Game::Startup()
{
	if (!engine.Init())
	{
		printf("Failed to initialize engine");
	}
}

void Game::Run()
{
	GameObject* player = CreatePlayer();

	engine.Run();
}

void Game::Quit()
{
	engine.Quit();
}

GameObject* Game::CreatePlayer()
{
	GameObject* player = objectFactory->CreateGameObject();
	Transform* playerTransform = (Transform*) objectFactory->AddComponent(player, "TRANSFORM");
	playerTransform->position.x = 5;
	playerTransform->position.y = 15;
	//objectFactory->AddComponent(player, "SPRITE");
	//objectFactory->AddComponent(player, "INPUT");

	return player;
}