#pragma once
#include "../Scene.h"
class AbilitySelect : public Scene
{
public:
	AbilitySelect(ObjectFactory* objectFactory);
	void Load();
	void Update();
	void HandleMessage(Message* msg);

private:
	int selection;
	int hovered;
};

