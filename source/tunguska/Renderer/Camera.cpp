#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	Position = glm::vec2(0.0f, 0.0f);
	Size = glm::vec2(512, 512);

	IsProjectionDirty = true;
	IsViewDirty = true;
}

void Camera::SetPosition(glm::vec2 position)
{
	IsViewDirty = true;
	Position = position;
}

void Camera::SetSize(glm::vec2 size)
{
	IsProjectionDirty = true;
	Size = size;
}

glm::vec2 Camera::GetPosition() { return Position; }
glm::vec2 Camera::GetSize() { return Size; }

glm::mat4 Camera::GetProjection()
{
	if (IsProjectionDirty)
	{
		Projection = glm::ortho(0.0f, Size.x, Size.y, 0.0f);

		IsProjectionDirty = false;
	}

	return Projection;
}

glm::mat4 Camera::GetView()
{
	if (IsViewDirty)
	{
		View = glm::mat4(1.0f);
		View = glm::translate(glm::mat4(1.0f),
			glm::vec3(Position.x, Position.y, 0.0f));

		IsViewDirty = false;
	}

	return View;
}