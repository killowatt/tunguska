#pragma once

#include "glm/mat4x4.hpp"

class Camera
{
	glm::mat4 Projection;
	glm::mat4 View;

	glm::vec2 Position;
	glm::vec2 Size;

	bool IsProjectionDirty;
	bool IsViewDirty;

public:
	Camera();

	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 resolution);

	glm::vec2 GetPosition();
	glm::vec2 GetSize();

	glm::mat4 GetProjection();
	glm::mat4 GetView();
};