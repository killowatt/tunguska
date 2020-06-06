#pragma once

#include "Common.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "ResourceManager.h"

#include "Entities/Switch.h"

#include <vector>

struct rdrcontact
{
	float angle;
	float dist;
};

class Scene
{
public:
	Renderer* Renderer;
	ResourceManager* ResourceManager;

	std::vector<Entity*> Entities;

	Switch RadarSwitch;
	Switch SecondSwitch;

	rdrcontact contac;

	Sprite* rdr;
	Sprite* testcontact;

	void Initialize();

	void Update();
	void Render();

	void OnClick(int32 x, int32 y);
};