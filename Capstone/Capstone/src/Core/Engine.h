#pragma once
#include "SDL.h"
#include <vector>
#include "System.h"
#include "Message.h"
#include "ObjectFactory.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640


class System;
class Engine
{
public:
	Engine();
	~Engine();
	bool Init();
	bool Quit();
	bool Run();
	static void BroadcastMessage(Message*);
	ObjectFactory objectFactory;

private:
	void Cleanup();

	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<System*> systems;
	static std::vector<Message*> messages;
};

/*
namespace Engine
{
	class System;

	bool Run();
	static void BroadcastMessage(Message*);
	ObjectFactory entityFactory;

	bool Init();
	bool Quit();
	void Cleanup();

	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<System*> systems;
	std::vector<Message*> messages;
}
*/

