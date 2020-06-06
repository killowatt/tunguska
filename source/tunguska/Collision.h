#pragma once

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

#include "Entity.h"

class Collision
{
public:
	static bool CheckCollision(glm::vec2 point, glm::vec4 rectangle);
};

class Collider
{
public:

	Entity* Parent;
	bool Enabled;

	glm::vec2 Position;
	glm::vec2 Size;
};