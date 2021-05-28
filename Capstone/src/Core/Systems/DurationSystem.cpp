#include "DurationSystem.h"
#include <chrono>
#include <iostream>

DurationSystem::DurationSystem(ObjectFactory * objectFactory)
{
	objectFactoryRef = objectFactory;
	durationComponents = &objectFactoryRef->durationComponents;
}

void DurationSystem::Init()
{
}

void DurationSystem::Update(Uint32 dt)
{
	if (isActive())
	{
		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

		for (int i = 0; i < durationComponents->size();)
		{
			Duration* duration = &durationComponents->at(i);
			if (duration->ttl > -1 && currentTime - duration->creationTime >= std::chrono::milliseconds(duration->ttl))
			{
				if (!duration->msgString.empty())
				{
					Message* msg = new Message();
					msg->id.assign(duration->msgString);
					Engine::BroadcastMessage(msg);
				}

				GameObject* obj = &objectFactoryRef->gameObjects.at(duration->gameObjectId);
				objectFactoryRef->DestroyGameObject(obj);
			}
			else
				i++;
		}
	}
}

void DurationSystem::HandleMessage(Message * msg)
{
}


void DurationSystem::setActive(bool is_active)
{
	// on to off
	if (isActive() && !is_active)
	{
		pauseTime = std::chrono::steady_clock::now();
		System::setActive(false);
	}
	// off to on
	else if (!isActive() && is_active)
	{
		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - pauseTime).count();
		printf("Pause time (ms): %d\n", dt);
		for (auto &duration : *durationComponents)
		{
			duration.ttl += dt;
		}
		System::setActive(true);
	}
}
