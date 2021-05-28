#pragma once
#include "../System.h"
#include "../Components/Physics.h"
#include "../Components/Transform.h"


class PhysicsSystem : public System
{
public:
	PhysicsSystem(ObjectFactory*);
	~PhysicsSystem();
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);

private:
	ObjectFactory* objectFactoryRef;
	std::vector<GameObject>* gameObjectsRef;
	std::vector<Physics>* physicsComponents;
	std::vector<Transform>* transformComponents;
	std::vector<Collider>*colliderComponents;
};

