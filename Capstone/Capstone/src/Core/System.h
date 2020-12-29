#pragma once
#include "Message.h"
#include "Engine.h"
class System
{
public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void HandleMessage(Message* msg) = 0;
	virtual ~System() {};
};