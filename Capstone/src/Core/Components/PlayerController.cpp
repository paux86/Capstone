#include "PlayerController.h"

PlayerController::PlayerController()
{
	damage = 100;
	
	special = -1;

	special_cooldown[0] = 2000;
	special_cooldown[1] = 2000;
	special_cooldown[2] = 0;

	special_modifier[0] = 8000; //duration
	special_modifier[1] = 8000; //duration
	special_modifier[2] = 50; //distance
	
	special_last_used = std::chrono::steady_clock::now() - std::chrono::milliseconds(100000);
}