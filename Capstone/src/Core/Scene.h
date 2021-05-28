#pragma once
#include "ObjectFactory.h"
#include "Components/CollisionLayer.h"
#include "Settings.h"
#include "Engine.h"


class Scene
{
public:
	Scene(ObjectFactory* objectFactory) { objectFactoryRef = objectFactory; };
	virtual void Load() = 0;
	void Unload() { objectFactoryRef->DestroyAllGameObjects(); };
	virtual void Update() = 0;
	virtual void HandleMessage(Message* msg) = 0;

	ObjectFactory* objectFactoryRef;
};

