#pragma once
#include "../Component.h"
#include <SDL.h>
#include <string>

class Sprite : public Component
{
public:
	Sprite();
	std::string spritePath;
	SDL_Texture* spriteTexture;
};

