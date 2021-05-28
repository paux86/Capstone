#pragma once
#include "../Component.h"
#include <chrono>
class PlayerController : public Component
{
public:
	PlayerController();

	int damage;

	// shield, circle, dodge
	int special;
	/// in milliseconds
	int special_cooldown[3];
	int special_modifier[3];

	std::chrono::steady_clock::time_point special_last_used;
};

