#pragma once
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Input.h"
#include "PlayerController.h"
#include "Collider.h"
#include "Health.h"
#include "Damage.h"
#include "EnemyController.h"
#include "Duration.h"
#include "FilledBar.h"

namespace Components
{
	enum ComponentType { TRANSFORM, SPRITE, PHYSICS, INPUT, PLAYERCONTROLLER, COLLIDER, HEALTH, DAMAGE, ENEMYCONTROLLER, DURATION, FILLEDBAR };
	static const ComponentType All[] = { TRANSFORM, SPRITE, PHYSICS, INPUT, PLAYERCONTROLLER, COLLIDER, HEALTH, DAMAGE, ENEMYCONTROLLER, DURATION, FILLEDBAR };
}