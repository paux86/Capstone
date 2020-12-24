#include "Engine.h"
#include "Systems/InputSystem.h"


Engine::Engine()
{
	if (Init())
	{
		Run();
	}
}

Engine::~Engine()
{
	Cleanup();
}

bool Engine::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Capstone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	systems.emplace_back(new InputSystem());

	return running = true;
}

bool Engine::Run()
{
	while (running)
	{
		for (auto system : systems)
		{
			//need to pass actual delta time
			system->Update(0.0);
		}
	}
	return true;
}

bool Engine::Quit()
{
	running = false;
	return true;
}

void Engine::Cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}