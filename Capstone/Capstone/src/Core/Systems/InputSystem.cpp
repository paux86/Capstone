#include "InputSystem.h"
#include "SDL.h"
#include <iostream>

InputSystem::InputSystem()
{

}

void InputSystem::Init()
{

}

void InputSystem::Update(float dt)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			std::cout << "Quit event\n";
			Message* msg = new Message();
			msg->id = "QUIT";
			Engine::BroadcastMessage(msg);
		}
	}
}

void InputSystem::HandleMessage(Message* msg)
{

}

InputSystem::~InputSystem()
{

}
