#include "Engine.h"
#include "Systems/InputSystem.h"
#include <iostream>

std::vector<Message*> Engine::messages;

Engine::Engine()
{
	if (Init())
	{
		std::cout << "Initialized\n";
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
		//handle messages (should try to implement pub-sub)
		while (!messages.empty())
		{
			Message* message = messages.back();
			messages.pop_back();
			if (message->id == "QUIT")
			{
				Quit();
			}
			for (auto system : systems)
			{
				system->HandleMessage(message);
			}
		}
		
		//update all systems
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
	std::cout << "Quit\n";
	running = false;
	return true;
}

void Engine::Cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::BroadcastMessage(Message* message)
{
	messages.push_back(message);
}