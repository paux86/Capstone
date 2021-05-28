#include "EnemyController.h"

EnemyController::EnemyController()
{
	aggroRange = 1000;
	attackRange = 200;
	attackCooldown = 1000;
	projectileSpeed = 2.f;
	projectileDuration = -1;
	projectileSpritePath = "./assets/sprites/bullet_red.png";
	movementSpeed = 1.f;
	lastAttackTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(attackCooldown);
}
