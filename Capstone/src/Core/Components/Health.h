#pragma once
#include "../Component.h"
class Health : public Component
{
public:
	Health();
	int max_health, current_health;
};

