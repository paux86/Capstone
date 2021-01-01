#pragma once
#include "../Component.h"
#include "../Vec2.h"

class Transform : public Component
{
public:
	Transform(Vec2);
	Vec2 position;
};

