#pragma once
#include "../Component.h"
#include <SDL.h>
class FilledBar : public Component
{
public:
	FilledBar();
	int width;
	int height;
	float fillPercent;
	SDL_Color BGcolor;
	SDL_Color FGcolor;
};

