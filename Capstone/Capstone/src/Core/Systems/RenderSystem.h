#pragma once
#include "../System.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include <vector>

class RenderSystem : public System
{
public:
	RenderSystem(std::vector<Transform>* transforms, std::vector<Sprite>* sprites);
	void Init();
	void Update();
	void HandleMessage(Message* msg);

private:
	bool loadFromFile(std::string path);
	void free();

	std::vector<Transform>* transformComponents;
	std::vector<Sprite>* spriteComponents;
};

