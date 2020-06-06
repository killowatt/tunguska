#include "Collision.h"

bool Collision::CheckCollision(glm::vec2 point, glm::vec4 rectangle)
{
	return (point.x > rectangle.x && point.x < rectangle.z &&
		point.y > rectangle.y && point.y < rectangle.w);
}