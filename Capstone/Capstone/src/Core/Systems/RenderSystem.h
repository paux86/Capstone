#pragma once
#include "../System.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include <vector>
#include <SDL_image.h>


class RenderSystem : public System
{
public:
	RenderSystem(SDL_Window* window, SDL_Renderer* renderer, std::vector<Transform>* transforms, std::vector<Sprite>* sprites);
	~RenderSystem();
	void Init();
	void Update(float dt);
	void HandleMessage(Message* msg);

private:
	bool loadSprite(Sprite&);
	void renderSprite(const Sprite&, const Transform&);
	void freeSprite(Sprite& sprite);
	void freeAllSprites();

	SDL_Window* windowRef;
	SDL_Renderer* rendererRef;
	std::vector<Transform>* transformComponents;
	std::vector<Sprite>* spriteComponents;
};

