#pragma once
#include "../Scene.h"

class Level : public Scene
{
public:
	Level(ObjectFactory* objectFactory, int stageNum, bool isDemo);
	void Load();
	void Update();
	void HandleMessage(Message* msg);

private:
	int score;
	int enemiesRemaining;
	int stageNumber;
	bool demo;
};

