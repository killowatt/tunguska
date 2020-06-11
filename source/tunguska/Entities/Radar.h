#pragma once

#include "Entity.h"
#include "Game/ExteriorEntity.h"
#include <unordered_map>

struct RadarContact
{
	float Time;
	glm::vec2 lkp;
};

class Radar : public Entity
{
private:
	float PreviousRadarRotation;
	float RadarRotation;

	float CurrentRange = 64.0f;

	Sprite RadarBackground;
	Sprite RadarForeground;
	Sprite RadarLine;
	Sprite contactsprite;

public:
	glm::vec3 WorldPosition;
	std::vector<ExteriorEntity>* Contacts;

	std::unordered_map<ExteriorEntity*, RadarContact> ExCon;

	bool ScreenIsPowered;
	bool RadarIsPowered;

	void Initialize(ResourceManager* resourceManager) override;

	void Update() override;
	void Render(Renderer* renderer) override;
};