#pragma once
#include "SDL.h"
#include <vector>
#include "System.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
public:
	Engine();
	~Engine();
	bool Init();
	bool Run();
	bool Quit();

private:
	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<System*> systems;

	void Cleanup();
};

