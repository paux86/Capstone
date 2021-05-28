#include "Title.h"

Title::Title(ObjectFactory* objectFactory) : Scene(objectFactory)
{
}

void Title::Load()
{
	GameObject* startButton = objectFactoryRef->CreateButton("Start", Settings::SCREEN_WIDTH / 2 - 20, Settings::SCREEN_HEIGHT / 2 - 50, 100, 20);
	startButton->AddTag("Start Button");

	GameObject* exitButton = objectFactoryRef->CreateButton("Exit", Settings::SCREEN_WIDTH / 2 - 20, Settings::SCREEN_HEIGHT / 2 + 50, 100, 20);
	exitButton->AddTag("Exit Button");
}

void Title::Update()
{
	GameObject* startButton = objectFactoryRef->GetObjectByTag("Start Button");
	Collider* startButtonCollider = (Collider*) objectFactoryRef->GetComponent(startButton, Components::COLLIDER);
	if (startButtonCollider->clicked)
	{
		//printf("Start button\n");
		Message* msg = new Message();
		//msg->id = "LOAD MODS";
		msg->id.assign("SELECT ABILITY");
		Engine::BroadcastMessage(msg);
	}

	GameObject* exitButton = objectFactoryRef->GetObjectByTag("Exit Button");
	Collider* exitButtonCollider = (Collider*)objectFactoryRef->GetComponent(exitButton, Components::COLLIDER);
	if (exitButtonCollider->clicked)
	{
		//printf("Exit button\n");
		Message* msg = new Message();
		msg->id = "QUIT";
		Engine::BroadcastMessage(msg);
	}
}

void Title::HandleMessage(Message * msg)
{
}
