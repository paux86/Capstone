#pragma once
#include "../Component.h"
#include <chrono>
class Damage : public Component
{
public:
	Damage();
	int value;
	uint32_t frequency;
	std::chrono::steady_clock::time_point lastTick;
};

