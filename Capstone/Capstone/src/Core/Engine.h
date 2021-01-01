#pragma once
#include "SDL.h"
#include <vector>
#include "System.h"
#include "Message.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class System;
class Engine
{
public:
	Engine();
	~Engine();
	bool Run();
	static void BroadcastMessage(Message*);

private:
	bool Init();
	bool Quit();
	void Cleanup();

	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<System*> systems;
	static std::vector<Message*> messages;
};

