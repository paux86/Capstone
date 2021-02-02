#pragma once
#include "../Component.h"
#include "../Vec2.h"

class Transform : public Component
{
public:
	Transform();
	Transform(Vec2<int>);
	Vec2<int> position;

};

