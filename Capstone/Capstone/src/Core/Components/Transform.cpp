#include "Transform.h"

/*
Transform::Transform()
{
	componentType = "TRANSFORM";
	position = Vec2<float>();
}
*/


Transform::Transform() : Transform(Vec2<int>())
{

}

Transform::Transform(Vec2<int> pos)
{
	componentType = "TRANSFORM";
	//TODO: change this after adding vec2 operator overloading
	position = Vec2<int>(pos.x, pos.y);
}
