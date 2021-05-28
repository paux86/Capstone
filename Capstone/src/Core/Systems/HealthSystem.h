#pragma once
#include "../System.h"
#include "../ObjectFactory.h"
class HealthSystem : public System
{
public:
	HealthSystem(ObjectFactory*);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);

private:
	ObjectFactory* objectFactoryRef;
	std::vector<Health>* healthComponents;
};

