#pragma once
#include "Message.h"
#include "Engine.h"
class System
{
public:
	virtual void Init() = 0;
	virtual void Update(Uint32 dt) = 0;
	virtual void HandleMessage(Message* msg) = 0;
	bool isActive() { return active; }
	virtual void setActive(bool is_active) { active = is_active; }
	virtual ~System() {};
private:
	bool active = true;
};