#pragma once
#include "../Scene.h"
class Title : public Scene
{
public:
	Title(ObjectFactory* objectFactory);
	void Load();
	void Update();
	void HandleMessage(Message* msg);
};

