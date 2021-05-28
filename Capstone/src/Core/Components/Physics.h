#pragma once
#include "../Component.h"
#include "../Vec2.h"
class Physics : public Component
{
public:
	Physics();
	Vec2<float> velocity;
	Vec2<float> acceleration;
	float movespeed;
	bool ignoreBounds;
};

