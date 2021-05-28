#pragma once
#include "../Scene.h"
class ModDisplay : public Scene
{
public:
	ModDisplay(ObjectFactory* objectFactory, float roundMulti);
	void Load();
	void Update();
	void HandleMessage(Message* msg);

private:
	int roundMultiplier;
	int mods[5];
};

