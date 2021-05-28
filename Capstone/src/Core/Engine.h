#pragma once
#include "SDL.h"
#include <vector>
#include "System.h"
#include "Message.h"
#include "ObjectFactory.h"
#include "Settings.h"



class System;
class Engine
{
public:
	Engine();
	~Engine();
	bool Init();
	bool Quit();
	bool Run();
	void TogglePause();
	static void BroadcastMessage(Message*);
	static Vec2<float> GetRelMousePos();
	void ToggleFullscreen();

	ObjectFactory objectFactory;

private:
	void Cleanup();

	bool running;
	bool paused;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<System*> systems;
	std::vector<int> pausedSystems;
	static std::vector<Message*> messages;
};
