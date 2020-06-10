#include "Entities/Radar.h"
#include "glm/gtc/matrix_transform.hpp"

void Radar::Initialize(ResourceManager* resourceManager)
{
	RadarBackground.Texture = resourceManager->LoadTexture("radarscreen.png");
	RadarForeground.Texture = resourceManager->LoadTexture("radarcover.png");
	RadarLine.Texture = resourceManager->LoadTexture("radar.png");

	RadarBackground.SetSize(128, 128);
	RadarForeground.SetSize(128, 128);
	RadarLine.SetSize(128, 128);

	RadarBackground.SetPosition(Position.x, Position.y);
	RadarForeground.SetPosition(Position.x, Position.y);
}

void Radar::Update()
{
	if (RadarIsPowered)
		RadarRotation += 0.075f;

	glm::mat4 lineTransform(1.0f);
	lineTransform = glm::translate(lineTransform,
		glm::vec3(Position, 0.0f));

	lineTransform = glm::translate(lineTransform,
		glm::vec3(64.0f, 64.0f, 0.0f));

	lineTransform = glm::rotate(lineTransform,
		RadarRotation,glm::vec3(0.0f, 0.0f, 1.0f));

	lineTransform = glm::translate(lineTransform,
		glm::vec3(-64.0f, -64.0f, 0.0f));

	lineTransform = glm::scale(lineTransform,
		glm::vec3(128.0f, 128.0f, 1));

	RadarLine.SetTransform(lineTransform);
}

void Radar::Render(Renderer* renderer)
{
	renderer->Draw(&RadarBackground);

	if (ScreenIsPowered)
		renderer->Draw(&RadarLine);

	renderer->Draw(&RadarForeground);
}