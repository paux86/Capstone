#pragma once
#include "../System.h"
class EnemyControllerSystem : public System
{
public:
	EnemyControllerSystem(ObjectFactory* objectFactory);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);

private:
	ObjectFactory* objectFactoryRef;
	std::vector<EnemyController>* enemyControllers;
};

