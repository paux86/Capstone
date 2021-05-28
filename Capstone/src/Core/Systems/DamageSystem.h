#pragma once
#include "../System.h"
#include "../ObjectFactory.h"
class DamageSystem : public System
{
public:
	DamageSystem(ObjectFactory* objectFactory);
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);

private:
	ObjectFactory* objectFactoryRef;
	std::vector<Damage>* damageComponents;
	std::vector<Health>* healthComponents;
	std::vector<Collider>* colliderComponents;
};

