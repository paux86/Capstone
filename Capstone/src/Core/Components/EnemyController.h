#pragma once
#include "../Component.h"
#include <chrono>
class EnemyController : public Component
{
public:
	EnemyController();
	float attackRange;
	float aggroRange;
	int attackCooldown;
	int attackDamage;
	float projectileSpeed;
	// milliseconds, default 5000
	int projectileDuration;
	std::string projectileSpritePath;
	float movementSpeed;
	std::chrono::steady_clock::time_point lastAttackTime;
};

