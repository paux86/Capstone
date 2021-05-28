#pragma once
#include "../Component.h"
#include "../Vec2.h"
#include <vector>

class Collider : public Component
{
public:
	Collider();
	Vec2<float> position;
	int width, height;
	bool collision;
	std::vector<int> collisionGameObjectIds;
	bool passable;
	int layer;
	bool hover;
	bool clicked;
};

