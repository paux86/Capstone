#include "Sprite.h"
#include "../Settings.h"

Sprite::Sprite()
{
	spriteTexture = NULL;
	width = height = Settings::TILE_SIZE;
	render_layer = 1;
}

Sprite::~Sprite()
{
	//TODO: this was destroying the texture on emplace, as the copy destructor is called
	/*
	if (spriteTexture != NULL)
	{
		SDL_DestroyTexture(spriteTexture);
		printf("Sprite: Obj: %d : Sprite texture destroyed, with path \n", gameObjectId, spritePath.c_str());
	}
	*/
}