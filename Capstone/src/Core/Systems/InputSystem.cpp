#include "InputSystem.h"
#include "SDL.h"
#include <iostream>

InputSystem::InputSystem(Input* inputRef) : inputComponent(inputRef)
{

}

void InputSystem::Init()
{

}

void InputSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		inputComponent->events.clear();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				//std::cout << "Quit event\n";
				Message* msg = new Message();
				msg->id.assign("QUIT");
				Engine::BroadcastMessage(msg);
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F10)
			{
				//printf("F10: Toggle full screen\n");
				Message* msg = new Message();
				msg->id.assign("TOGGLE FULLSCREEN");
				Engine::BroadcastMessage(msg);
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11)
			{
				//printf("F10: Toggle fps display\n");
				Message* msg = new Message();
				msg->id.assign("TOGGLE FPS");
				Engine::BroadcastMessage(msg);
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			{
				Message* msg = new Message();
				msg->id.assign("TOGGLE PAUSE");
				Engine::BroadcastMessage(msg);
			}
			else
			{
				inputComponent->events.push_back(event);
			}
		}
	}
}

void InputSystem::HandleMessage(Message* msg)
{
	if (msg->id == "QUIT")
	{

	}
}

InputSystem::~InputSystem()
{

}
