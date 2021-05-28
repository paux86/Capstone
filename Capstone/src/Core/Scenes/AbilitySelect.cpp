#include "AbilitySelect.h"

AbilitySelect::AbilitySelect(ObjectFactory * objectFactory) : Scene(objectFactory)
{
	selection = hovered = -1;
}

void AbilitySelect::Load()
{
	// header text
	objectFactoryRef->CreateText("Select an ability:", 330, 100);

	// shield
	GameObject* shieldButton = objectFactoryRef->CreateButton("", 250, 200, 64, 64);
	Sprite* shieldButtonSprite = (Sprite*)objectFactoryRef->GetComponent(shieldButton, Components::SPRITE);
	shieldButtonSprite->spritePath.assign("./assets/sprites/shield_with_cross_icon.png");
	shieldButton->AddTag("SELECT SHIELD");

	// dodge
	GameObject* dodgeButton = objectFactoryRef->CreateButton("", 425, 200, 64, 64);
	Sprite* dodgeButtonSprite = (Sprite*)objectFactoryRef->GetComponent(dodgeButton, Components::SPRITE);
	dodgeButtonSprite->spritePath.assign("./assets/sprites/hero_dash_icon.png");
	dodgeButton->AddTag("SELECT DODGE");

	// spell
	GameObject* spellButton = objectFactoryRef->CreateButton("", 600, 200, 64, 64);
	Sprite* spellButtonSprite = (Sprite*)objectFactoryRef->GetComponent(spellButton, Components::SPRITE);
	spellButtonSprite->spritePath.assign("./assets/sprites/spell_circle_green_icon.png");
	spellButton->AddTag("SELECT SPELL");
}

void AbilitySelect::Update()
{
	int textPosX = 200;
	int textPosY = 325;

	GameObject* shieldButton = objectFactoryRef->GetObjectByTag("SELECT SHIELD");
	Collider* shieldButtonCollider = (Collider*)objectFactoryRef->GetComponent(shieldButton, Components::COLLIDER);
	if (shieldButtonCollider->clicked)
	{
		selection = 0;
	}
	if (shieldButtonCollider->hover && hovered != 0)
	{
		hovered = 0;
		GameObject* hoverText = objectFactoryRef->GetObjectByTag("HOVER TEXT");
		if (hoverText)
		{
			objectFactoryRef->DestroyGameObject(hoverText);
		}
		GameObject* updatedHoverText = objectFactoryRef->CreateText("Drop a barrier that blocks projectiles", textPosX, textPosY);
		updatedHoverText->AddTag("HOVER TEXT");
	}

	GameObject* dodgeButton = objectFactoryRef->GetObjectByTag("SELECT DODGE");
	Collider* dodgeButtonCollider = (Collider*)objectFactoryRef->GetComponent(dodgeButton, Components::COLLIDER);
	if (dodgeButtonCollider->clicked)
	{
		selection = 2;
	}
	if (dodgeButtonCollider->hover && hovered != 1)
	{
		hovered = 1;
		GameObject* hoverText = objectFactoryRef->GetObjectByTag("HOVER TEXT");
		if (hoverText)
		{
			objectFactoryRef->DestroyGameObject(hoverText);
		}
		GameObject* updatedHoverText = objectFactoryRef->CreateText("Quickly dash to avoid enemy attacks", textPosX + 10, textPosY);
		updatedHoverText->AddTag("HOVER TEXT");
	}

	GameObject* spellButton = objectFactoryRef->GetObjectByTag("SELECT SPELL");
	Collider* spellButtonCollider = (Collider*)objectFactoryRef->GetComponent(spellButton, Components::COLLIDER);
	if (spellButtonCollider->clicked)
	{
		selection = 1;
	}
	if (spellButtonCollider->hover && hovered != 2)
	{
		hovered = 2;
		GameObject* hoverText = objectFactoryRef->GetObjectByTag("HOVER TEXT");
		if (hoverText)
		{
			objectFactoryRef->DestroyGameObject(hoverText);
		}
		GameObject* updatedHoverText = objectFactoryRef->CreateText("Create a circle that heals the player and damages enemies", 50, textPosY);
		updatedHoverText->AddTag("HOVER TEXT");
	}

	if (selection != -1)
	{
		// TODO: this ordering looks dumb, but my messages are processed LIFO and this order matters, maybe make it a proper queue
		Message* loadScene_msg = new Message();
		loadScene_msg->id.assign("LOAD MODS");
		Engine::BroadcastMessage(loadScene_msg);

		Message* updateAbility_msg = new Message();
		updateAbility_msg->id.assign("UPDATE ABILITY");
		updateAbility_msg->data = static_cast<void*>(&selection);
		Engine::BroadcastMessage(updateAbility_msg);

	}
}

void AbilitySelect::HandleMessage(Message * msg)
{
}
