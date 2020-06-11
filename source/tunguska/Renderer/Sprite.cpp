#include "Sprite.h"
#include "glm/gtc/matrix_transform.hpp"

Sprite::Sprite()
{
	CurrentFrame = 0;
	IsTransformDirty = true;

	Opacity = 1.0f;
}

glm::mat4 Sprite::GetTransform()
{
	if (IsTransformDirty)
	{
		Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f));
		Transform = glm::scale(Transform, glm::vec3(Size, 1.0f));
	}

	return Transform;
}

void Sprite::SetPosition(float x, float y)
{
	Position = glm::vec2(x, y);
	IsTransformDirty = true;
}

void Sprite::SetSize(float x, float y)
{
	Size = glm::vec2(x, y);
	IsTransformDirty = true;
}

void Sprite::SetTransform(glm::mat4 transform)
{
	Transform = transform;
	IsTransformDirty = false;
}
