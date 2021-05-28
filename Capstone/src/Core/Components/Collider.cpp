#include "Collider.h"
#include "../Settings.h"

Collider::Collider()
{
	width = height = Settings::TILE_SIZE;
	collision = false;
	//collisionGameObjectId = -1;
	passable = false;
	layer = 0;
	hover = false;
	clicked = false;
}
