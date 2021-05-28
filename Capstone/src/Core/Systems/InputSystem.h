#pragma once
#include "../System.h"
class InputSystem : public System
{
public:
	InputSystem(Input* inputRef);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);
	~InputSystem();
private:
	Input* inputComponent;
};