#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Window* window, SDL_Renderer* renderer, std::vector<Transform>* transforms, std::vector<Sprite>* sprites)
{
	windowRef = window;
	rendererRef = renderer;
	transformComponents = transforms;
	spriteComponents = sprites;
	Init();
}

RenderSystem::~RenderSystem()
{
	freeAllSprites();
	IMG_Quit();
}

void RenderSystem::Init()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Failed to initialize SDL_image, with error: %s\n", IMG_GetError());
		//TODO: should return false, all system inits should return success bool
	}
}

void RenderSystem::Update(float dt)
{
	//clear screen
	SDL_RenderClear(rendererRef);

	for (auto sprite : *spriteComponents)
	{
		//TODO: allow for path change to update texture
		//load unloaded sprites
		if (sprite.spriteTexture == nullptr && !sprite.spritePath.empty())
		{
			loadSprite(sprite);
		}

		//if object with sprite has a transform (they all should) then render
		Transform transform = *(Transform*)sprite.p_GameObject->GetComponent("TRANSFORM");
		renderSprite(sprite, transform);
	}

	//update screen
	SDL_RenderPresent(rendererRef);
}

void RenderSystem::HandleMessage(Message * msg)
{
}

bool RenderSystem::loadSprite(Sprite& sprite)
{
	bool success = true;

	SDL_Surface* surface = IMG_Load(sprite.spritePath.c_str());
	if (surface == NULL)
	{
		printf("Failed to load image %s, with SDL_image Error: %s\n", sprite.spritePath.c_str(), IMG_GetError());
	}
	else
	{
		sprite.spriteTexture = SDL_CreateTextureFromSurface(rendererRef, surface);
		if (sprite.spriteTexture == NULL)
		{
			printf("Failed to create texture from %s, with SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(surface);
	}

	return success;
}

void RenderSystem::renderSprite(const Sprite& sprite, const Transform& transform)
{
	//TODO: create proper sdl rects for sprite placement
	//TODO: implement sprite sheet rects
	SDL_RenderCopy(rendererRef, sprite.spriteTexture, NULL, NULL);
}

void RenderSystem::freeSprite(Sprite& sprite)
{
	SDL_DestroyTexture(sprite.spriteTexture);
	sprite.spriteTexture = NULL;
}

void RenderSystem::freeAllSprites()
{
	for (auto sprite : *spriteComponents)
	{
		freeSprite(sprite);
	}
}