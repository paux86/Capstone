#pragma once
#include "../Component.h"
#include "SDL.h"
#include <vector>
class Input : public Component
{
public:
	Input();
	static std::vector<SDL_Event> events;
};

