#pragma once
#include "../System.h"
#include "../Scene.h"
#include "../Scenes/Scenes.h"


class GameLogicSystem : public System
{
public:
	GameLogicSystem(ObjectFactory* objectFactoryRef);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);
	~GameLogicSystem();

private:
	void loadScene();
	void applyModifiers(std::vector<int> mods);

	ObjectFactory* objectFactoryRef;
	Scene* currentScene;
	// damage, attack rate, cooldown, movespeed, health
	std::vector<int> currentModifiers;
	// shield, spell, dodge
	int currentAbility;
	int currentStageNumber;
	float enemyScalingMultiplier;
};

