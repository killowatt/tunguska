#pragma once

#include "Common.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

#include "Entities/Switch.h"
#include "Entities/Radar.h"

#include <vector>

class Scene
{
public:
	Renderer* Renderer;
	ResourceManager* ResourceManager;

	glm::vec2 OurPosition;

	glm::vec2 firstcontact;
	glm::vec2 secondcontact;
	glm::vec2 stationarytarg;

	std::vector<Entity*> Entities;
	std::vector<glm::vec2*> Contacts;

	Radar RadarSystem;

	Switch RadarSwitch;
	Switch SecondSwitch;

	Sprite* testcontact;
	Sprite* testcontact2;
	Sprite* stationary;

	glm::vec2* targpos;
	Sprite* selectedtarget;

	void Initialize();

	void Update();
	void Render();

	void OnClick(int32 x, int32 y);

	void fugg(glm::vec2 vec, Sprite* outspr, float lastrdr, float currrdr);
	void nexttarg();
};