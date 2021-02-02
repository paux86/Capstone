#pragma once
#include "Engine.h"

class Game
{
public:
	Game();
	~Game();
	void Startup();
	void Run();
	void Quit();

private:
	Engine engine;
	ObjectFactory* objectFactory;

	GameObject* CreatePlayer();
};

