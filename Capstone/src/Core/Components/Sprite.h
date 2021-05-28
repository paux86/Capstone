#pragma once
#include "../Component.h"
#include <SDL.h>
#include <string>

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();
	std::string spritePath;
	std::string spriteText;
	SDL_Texture* spriteTexture;
	int width, height;
	int render_layer;
};

