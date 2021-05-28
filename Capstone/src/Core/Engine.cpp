#include "Engine.h"
#include "Systems/Systems.h"
#include <iostream>


std::vector<Message*> Engine::messages;

Engine::Engine()
{
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

	window = SDL_CreateWindow("Capstone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, 0);
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

	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//SDL_RenderSetLogicalSize(renderer, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);
	//SDL_GetWindowSize(window, &Settings::WINDOW_WIDTH, &Settings::WINDOW_HEIGHT);

	// Updated in order, so order very important
	systems.emplace_back(new InputSystem(&objectFactory.inputComponent)); //0
	systems.emplace_back(new PlayerControllerSystem(&objectFactory)); //1
	systems.emplace_back(new EnemyControllerSystem(&objectFactory)); //2
	systems.emplace_back(new PhysicsSystem(&objectFactory)); //3
	systems.emplace_back(new DamageSystem(&objectFactory)); //4
	systems.emplace_back(new HealthSystem(&objectFactory)); //5
	systems.emplace_back(new GameLogicSystem(&objectFactory)); //6
	systems.emplace_back(new DurationSystem(&objectFactory)); //7
	systems.emplace_back(new RenderSystem(window, renderer, &objectFactory.gameObjects, &objectFactory.transformComponents, &objectFactory.spriteComponents, &objectFactory.filledbarComponents)); //8

	// list of system indexes to be paused on pause
	int indices[] = { 1, 2, 3, 4, 5, 7 };
	pausedSystems.assign(indices, indices + 6);

	//initialize all systems
	//TODO: update system init to return success, exit or failed init
	for (auto &system : systems)
	{
		system->Init();
	}

	paused = false;
	return running = true;
}

bool Engine::Run()
{
	const int TICKS_PER_FRAME = 1000 / Settings::FPS_LIMIT;
	Uint32 lastTime = SDL_GetTicks();
	while (running)
	{	
		Uint32 currentTime = SDL_GetTicks();
		Uint32 dt = currentTime - lastTime;
		lastTime = currentTime;

		if (dt < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - dt);
		}

		//handle messages
		while (!messages.empty())
		{
			Message* message = messages.back();
			messages.pop_back();
			if (message->id == "QUIT")
			{
				Quit();
			}
			else if (message->id == "TOGGLE FULLSCREEN")
			{
				ToggleFullscreen();
			}
			else if (message->id == "TOGGLE PAUSE")
			{
				TogglePause();
			}
			for (auto& system : systems)
			{
				system->HandleMessage(message);
			}
			delete(message);
		}
		
		//update all systems
		for (auto& system : systems)
		{
			//need to pass actual delta time
			system->Update(dt);
		}
	}
	return true; //why did i make this return anything??
}

// TODO: maybe each system should decide how it handles pausing instead.. probably, so i'm not hard coding system indexes
void Engine::TogglePause()
{
	paused = !paused;
	if (paused)
	{
		for (auto i : pausedSystems)
		{
			systems[i]->setActive(false);
		}
	}
	else
	{
		for (auto system : systems)
		{
			system->setActive(true);
		}
	}
}

bool Engine::Quit()
{
	std::cout << "Quit\n";
	running = false;
	return true;
}

void Engine::Cleanup()
{
	for (auto& system : systems)
	{
		delete system;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::BroadcastMessage(Message* message)
{
	messages.push_back(message);
}


Vec2<float> Engine::GetRelMousePos()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vec2<float> relMousePos = Vec2<float>(((float)x / Settings::WINDOW_WIDTH) * Settings::SCREEN_WIDTH, ((float)y / Settings::WINDOW_HEIGHT) * Settings::SCREEN_HEIGHT);
	//printf("Window: %d, %d\nScreen: %d, %d\nMouse: %d, %d\nRelMouse: %d, %d\n", (int)Settings::WINDOW_WIDTH, (int)Settings::WINDOW_HEIGHT, (int)Settings::SCREEN_WIDTH, (int)Settings::SCREEN_HEIGHT, x, y, (int)relMousePos.x, (int)relMousePos.y);
	return relMousePos;
}

void Engine::ToggleFullscreen()
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
	SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_RenderSetLogicalSize(renderer, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);
	SDL_GetWindowSize(window, &Settings::WINDOW_WIDTH, &Settings::WINDOW_HEIGHT);
}