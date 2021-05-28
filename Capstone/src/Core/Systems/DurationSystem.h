#pragma once
#include "../System.h"
class DurationSystem : public System
{
public:
	DurationSystem(ObjectFactory* objectFactory);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);
	void setActive(bool is_active);

private:
	ObjectFactory* objectFactoryRef;
	std::vector<Duration>* durationComponents;
	std::chrono::steady_clock::time_point pauseTime;
};

