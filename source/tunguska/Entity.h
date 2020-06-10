#pragma once

#include "Common.h"
#include "glm/vec2.hpp"

#include "ResourceManager.h"
#include "Renderer/Renderer.h"

class Entity
{
public:
	Entity();

	bool IsEnabled;

	glm::vec2 Position;
	glm::vec2 Scale;

	virtual void Initialize(ResourceManager* resourceManager) {};

	virtual void Update() {};
	virtual void Render(Renderer* renderer) {};

	virtual void OnClick(int32 x, int32 y) {};

	//std::vector<Component> Components;
};