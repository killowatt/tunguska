#pragma once

#include "Common.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

class Sprite : NonCopyable
{
	glm::mat4 Transform;
	bool IsTransformDirty;

	glm::vec2 Position;
	glm::vec2 Size;

public:
	Sprite();

	glm::mat4 GetTransform();

	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	void SetTransform(glm::mat4 transform);

	int32 CurrentFrame;

	class Texture* Texture;
	class Shader* Shader;
};