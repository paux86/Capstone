#pragma once
#include "../System.h"
class InputSystem : public System
{
public:
	InputSystem();
	void Init();
	void Update(float dt);
	void HandleMessage(Message* msg);
	~InputSystem();
};