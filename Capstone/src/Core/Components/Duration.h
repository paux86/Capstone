#pragma once
#include "../Component.h"
#include <chrono>

class Duration : public Component
{
public:
	Duration();

	std::chrono::steady_clock::time_point creationTime;
	// milliseconds
	int ttl;
	std::string msgString;
};

