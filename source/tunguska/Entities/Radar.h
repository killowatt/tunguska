#pragma once

#include "Entity.h"


class Radar : public Entity
{
private:
	float RadarRotation;

	Sprite RadarBackground;
	Sprite RadarForeground;
	Sprite RadarLine;

public:
	bool ScreenIsPowered;
	bool RadarIsPowered;

	void Initialize(ResourceManager* resourceManager) override;

	void Update() override;
	void Render(Renderer* renderer) override;
};