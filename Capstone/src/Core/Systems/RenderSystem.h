#pragma once
#include "../System.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>


class RenderSystem : public System
{
public:
	RenderSystem(SDL_Window* window, SDL_Renderer* renderer, std::vector<GameObject>* gameObjects, std::vector<Transform>* transforms, std::vector<Sprite>* sprites, std::vector<FilledBar>* filledbars);
	~RenderSystem();
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);

private:
	bool loadSprite(Sprite&);
	bool loadSpriteFromText(Sprite& sprite, std::string text, SDL_Color color);
	void renderSprite(const Sprite&, const Transform&);
	void renderFilledBar(const FilledBar& bar, const Transform& barTransform);
	void freeSprite(Sprite& sprite);
	void freeAllSprites();

	SDL_Window* windowRef;
	SDL_Renderer* rendererRef;
	std::vector<GameObject>* gameObjectsRef;
	std::vector<Transform>* transformComponents;
	std::vector<Sprite>* spriteComponents;
	std::vector<FilledBar>* filledbarComponents;
	TTF_Font* font;
	
	bool show_fps;
	Sprite fps;
	Transform fps_position;
};

