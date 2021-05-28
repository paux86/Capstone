#include "RenderSystem.h"
#include <algorithm>
#include <tuple>

RenderSystem::RenderSystem(SDL_Window* window, SDL_Renderer* renderer, std::vector<GameObject>* gameObjects, std::vector<Transform>* transforms, std::vector<Sprite>* sprites, std::vector<FilledBar>* filledbars)
{
	windowRef = window;
	rendererRef = renderer;
	gameObjectsRef = gameObjects;
	transformComponents = transforms;
	spriteComponents = sprites;
	filledbarComponents = filledbars;
	font = NULL;
	
	show_fps = false;
	fps_position.position.x = Settings::SCREEN_WIDTH - 100;
	fps_position.position.y = Settings::SCREEN_HEIGHT - 20;
}

RenderSystem::~RenderSystem()
{
	freeAllSprites();
	IMG_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
}

void RenderSystem::Init()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("Failed to initialize SDL_image, with error: %s\n", IMG_GetError());
		//TODO: should return false, all system inits should return success bool
	}

	if (TTF_Init() == -1)
	{
		printf("Failed to initialize TTF_font, with error: %s\n", TTF_GetError());
	}

	font = TTF_OpenFont("./assets/fonts/lazy.ttf", 28);
	
	if (font == NULL)
	{
		printf("Failed to load font, with error %s\s", TTF_GetError());
	}
}

void RenderSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		//clear screen
		SDL_RenderClear(rendererRef);

		//get render order, without reordering game objects
		std::vector<std::tuple<int, int>> renderOrder;
		int spriteLen = spriteComponents->size();
		for (int i = 0; i < spriteLen; i++)
		{
			renderOrder.push_back(std::tuple<int, int>(spriteComponents->at(i).render_layer, i));
		}
		std::sort(renderOrder.begin(), renderOrder.end());

		//render active sprites
		for (int i = 0; i < spriteLen; i++)
		{
			Sprite* sprite = &spriteComponents->at(std::get<1>(renderOrder[i]));
			if (sprite->active)
			{
				//TODO: allow for path change to update texture
				//load unloaded sprites
				if (sprite->spriteTexture == NULL && !sprite->spritePath.empty())
				{
					//printf("Loading sprite at path: %s\n", sprite.spritePath.c_str());
					loadSprite(*sprite);
				}
				else if (sprite->spriteTexture == NULL && !sprite->spriteText.empty())
				{
					//printf("Loading sprite from text\n");
					//SDL_Color textColor = { 0, 0, 0, 0 };
					SDL_Color textColor = { 255, 255, 255, 0 };
					loadSpriteFromText(*sprite, sprite->spriteText, textColor);
				}

				//if object with sprite has a transform (they all should) then render
				if (gameObjectsRef->at(sprite->gameObjectId).HasComponent(Components::TRANSFORM))
				{
					int transformIndex = gameObjectsRef->at(sprite->gameObjectId).GetComponentIndex(Components::TRANSFORM);
					Transform* transform = &transformComponents->at(transformIndex);
					renderSprite(*sprite, *transform);
				}
			}
		}

		//render active filledbars
		for (auto &bar : *filledbarComponents)
		{
			if (gameObjectsRef->at(bar.gameObjectId).HasComponent(Components::TRANSFORM))
			{
				int transformIndex = gameObjectsRef->at(bar.gameObjectId).GetComponentIndex(Components::TRANSFORM);
				Transform* transform = &transformComponents->at(transformIndex);
				renderFilledBar(bar, *transform);
			}
		}

		// TODO: update less frequently
		//display fps if enabled
		if (show_fps)
		{
			SDL_Color textColor = { 255, 255, 255, 0 };
			if (dt > 0)
			{
				loadSpriteFromText(fps, "FPS: " + std::to_string((Uint32)1000 / dt), textColor);
				renderSprite(fps, fps_position);
			}
			else
			{
				loadSpriteFromText(fps, "FPS: inf", textColor);
				renderSprite(fps, fps_position);
			}
		}

		//update screen
		SDL_RenderPresent(rendererRef);
	}
}

void RenderSystem::HandleMessage(Message * msg)
{
	if (msg->id == "QUIT")
	{

	}
	else if (msg->id == "TOGGLE FPS")
	{
		show_fps = !show_fps;
	}
}

bool RenderSystem::loadSprite(Sprite& sprite)
{
	bool success = true;

	if (sprite.spriteTexture != NULL)
	{
		SDL_DestroyTexture(sprite.spriteTexture);
	}
	
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
			printf("Failed to create texture from %s, with SDL Error: %s\n", sprite.spritePath.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(surface);
	}

	//printf("Sprite loaded\n");
	return success;
}

bool RenderSystem::loadSpriteFromText(Sprite& sprite, std::string text, SDL_Color color)
{
	if (sprite.spriteTexture != NULL)
	{
		SDL_DestroyTexture(sprite.spriteTexture);
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		printf("Failed to load surface from text, with error: %s", TTF_GetError());
	}
	else
	{
		sprite.spriteTexture = SDL_CreateTextureFromSurface(rendererRef, surface);
		if (sprite.spriteTexture == NULL)
		{
			printf("Failed to create texture from text, with SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			sprite.width = surface->w;
			sprite.height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	return sprite.spriteTexture != NULL;
}

void RenderSystem::renderSprite(const Sprite& sprite, const Transform& transform)
{
	//TODO: implement sprite sheet rects
	SDL_Rect renderQuad = { transform.position.x, transform.position.y, sprite.width, sprite.height };
	SDL_RenderCopy(rendererRef, sprite.spriteTexture, NULL, &renderQuad);
}

void RenderSystem::renderFilledBar(const FilledBar& bar, const Transform& barTransform)
{
	float percent = bar.fillPercent > 1.f ? 1.f : bar.fillPercent < 0.f ? 0.f : bar.fillPercent;
	//SDL_Color oldDrawColor;
	//SDL_GetRenderDrawColor(rendererRef, &oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.g, &oldDrawColor.a);
	SDL_Rect bgrect = { barTransform.position.x, barTransform.position.y, bar.width, bar.height };
	SDL_SetRenderDrawColor(rendererRef, bar.BGcolor.r, bar.BGcolor.g, bar.BGcolor.b, bar.BGcolor.a);
	SDL_RenderFillRect(rendererRef, &bgrect);
	SDL_SetRenderDrawColor(rendererRef, bar.FGcolor.r, bar.FGcolor.g, bar.FGcolor.b, bar.FGcolor.a);
	int pw = (int)((float)bar.width * percent);
	int px = barTransform.position.x;// +(bar.width - pw);
	SDL_Rect fgrect = { px, barTransform.position.y, pw, bar.height };
	SDL_RenderFillRect(rendererRef, &fgrect);
	//SDL_SetRenderDrawColor(rendererRef, oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);
	SDL_SetRenderDrawColor(rendererRef, 0, 0, 0, 255);
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