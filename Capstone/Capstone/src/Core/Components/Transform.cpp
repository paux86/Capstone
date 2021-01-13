#include "Transform.h"

Transform::Transform()
{
	position = Vec2();
}

Transform::Transform(Vec2 pos)
{
	position = Vec2(pos.x, pos.y);
}