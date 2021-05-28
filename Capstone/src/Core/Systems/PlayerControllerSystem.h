#pragma once
#include "../System.h"
class PlayerControllerSystem : public System
{
public:
	PlayerControllerSystem(ObjectFactory* objectFactory);
	~PlayerControllerSystem();
	void Init();
	void Update(Uint32 dt);
	void HandleMessage(Message* msg);
	void setActive(bool is_active);

private:
	void createShield(PlayerController& playerComponent, Transform* playerTransform);
	void createCircle(GameObject* player, PlayerController& playerComponent, Transform* playerTransform);
	void dodge(GameObject* player, PlayerController& playerComponent, Physics* playerPhysics, Transform* playerTransform);

	ObjectFactory* objectFactoryRef;
};

