#pragma once

#include "Entity.h"
#include "Collision.h"
#include "Renderer/Sprite.h"
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

class Switch : public Entity
{
public:
	bool State = false;

	Texture* SwitchBase;
	Texture* SwitchUp;
	Texture* SwitchDown;

	Collider Bruh;
	Sprite Base;
	Sprite Flicker;

	void Initialize(ResourceManager* resourceManager);

	void Update() override;
	void Render(Renderer* renderer) override;

	void OnClick(int32 x, int32 y) override;

	void UpdateSwitchState();
};