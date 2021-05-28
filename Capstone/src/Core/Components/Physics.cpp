#include "Physics.h"

Physics::Physics()
{
	velocity = Vec2<float>(0.0, 0.0);
	acceleration = Vec2<float>(0.0, 0.0);
	movespeed = 1.f;
	ignoreBounds = false;
}