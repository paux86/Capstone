#include "ModDisplay.h"
#include <stdlib.h>
#include <time.h>
#include "../Settings.h"

ModDisplay::ModDisplay(ObjectFactory * objectFactory, float roundMulti) : Scene(objectFactory)
{
	roundMultiplier = roundMulti * 100;
}

void ModDisplay::Load()
{
	srand(time(NULL));
	const int numMods = 5;

	for (auto &mod : mods)
	{
		mod = rand() % 2;
	}

	objectFactoryRef->CreateText("=Stage Modifiers=", Settings::SCREEN_WIDTH / 2 - 125, 175);

	std::string roundMultiString = "Round multiplier (+" + std::to_string(roundMultiplier) + "% enemy stats)";
	objectFactoryRef->CreateText(roundMultiString, Settings::SCREEN_WIDTH / 4, 275);
	
	int modsApplied = 0;
	std::vector<std::string> modText { "Damage increased", "Attack Rate increased", "Reduced cooldowns", "Movespeed increased", "Double health" };
	for (int i = 0; i < numMods; i++)
	{
		if (mods[i] == 1)
		{
			objectFactoryRef->CreateText(modText[i], Settings::SCREEN_WIDTH / 4, 295 + (modsApplied * 20));
			modsApplied++;
		}
	}

	Message* msg = new Message();
	msg->id.assign("UPDATE MODS");
	msg->data = static_cast<void*>(&mods);
	Engine::BroadcastMessage(msg);
}

void ModDisplay::Update()
{
	for (auto event : objectFactoryRef->inputComponent.events)
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			Message* msg = new Message();
			msg->id.assign("LOAD LEVEL");
			Engine::BroadcastMessage(msg);
		}
	}
}

void ModDisplay::HandleMessage(Message * msg)
{

}
