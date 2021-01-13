#include "Engine.h"

int main(int argc, char* args[])
{
	Engine engine;

	Entity ent = engine.entityFactory.CreateEntity();
	Transform* ent_transform = (Transform*)engine.entityFactory.AddComponent(ent, "TRANSFORM");
	ent_transform->position.x = 1;
	ent_transform->position.y = 1;

	engine.Run();

	return 0;
}