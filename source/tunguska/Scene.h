#pragma once

#include "Common.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

#include "Entities/Switch.h"
#include "Entities/Radar.h"

#include "Game/ExteriorEntity.h"

#include <vector>

class Scene
{
public:
	Renderer* Renderer;
	ResourceManager* ResourceManager;

	glm::vec2 OurPosition;

	std::vector<Entity*> Entities;
	std::vector<ExteriorEntity> Contacts;

	Radar RadarSystem;

	Switch RadarSwitch;
	Switch SecondSwitch;

	void Initialize();

	void Update();
	void Render();

	void OnClick(int32 x, int32 y);
};