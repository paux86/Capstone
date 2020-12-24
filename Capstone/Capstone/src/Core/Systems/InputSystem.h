#pragma once
#include "../System.h"
class InputSystem : public System
{
public:
	InputSystem();
	void Init();
	void Update(float dt);
	~InputSystem();
};