#include "Entities/Radar.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

void Radar::Initialize(ResourceManager* resourceManager)
{
	RadarBackground.Texture = resourceManager->LoadTexture("radarscreen.png");
	RadarForeground.Texture = resourceManager->LoadTexture("radarcover.png");
	RadarLine.Texture = resourceManager->LoadTexture("radar.png");
	contactsprite.Texture = resourceManager->LoadTexture("contact.png");

	RadarBackground.SetSize(128, 128);
	RadarForeground.SetSize(128, 128);
	RadarLine.SetSize(128, 128);
	contactsprite.SetSize(2, 2);

	RadarBackground.SetPosition(Position.x, Position.y);
	RadarForeground.SetPosition(Position.x, Position.y);
}

void Radar::Update()
{
	if (RadarIsPowered)
		RadarRotation += (2 * glm::pi<float>()) / 60.0f;

	if (RadarRotation > 2 * glm::pi<float>())
	{
		PreviousRadarRotation =
			RadarRotation - PreviousRadarRotation;
		RadarRotation = 0.0f;
	}

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

	if (!RadarIsPowered)
		return; // We're finished, don't update contacts

	for (ExteriorEntity& entity : *Contacts)
	{
		// check against extent last frame position too
		// (potential edge case where we dont see contact)

		if (glm::distance(entity.Position, WorldPosition) > CurrentRange)
			continue; // Outside of our range

		glm::vec2 position = glm::normalize(entity.Position);
		glm::vec2 right = glm::vec2(1.0f, 0.0f);

		float angle = glm::angle(right, position);

		if (position.y < 0.0f)
			angle = 2 * glm::pi<float>() - angle;

		if (angle <= RadarRotation &&
			angle >= PreviousRadarRotation)
		{
			auto uhh = ExCon.find(&entity);
			if (uhh != ExCon.end())
			{
				uhh->second.Time = 1.0f;
				uhh->second.lkp = entity.Position;
			}
			else
			{
				RadarContact newcon;
				newcon.Time = 1.0f;
				newcon.lkp = entity.Position;

				std::pair<ExteriorEntity*, RadarContact> okbuddy(
					&entity, newcon);
				ExCon.insert(okbuddy);
			}
		}
	}

	for (auto rdrc = ExCon.begin(); rdrc != ExCon.end();)
	{
		rdrc->second.Time -= 1.0f / 120.0f;

		if (rdrc->second.Time <= 0.0f)
		{
			rdrc = ExCon.erase(rdrc);
		}
		else
		{
			rdrc++;
		}
	}

	PreviousRadarRotation = RadarRotation;
}

void Radar::Render(Renderer* renderer)
{
	renderer->Draw(&RadarBackground);

	if (ScreenIsPowered)
	{
		for (auto& contac : ExCon)
		{
			contactsprite.SetPosition(
				contac.second.lkp.x + Position.x + 64,
				contac.second.lkp.y + Position.y + 64);

			contactsprite.Opacity = 
				std::min(1.0f, contac.second.Time);

			renderer->Draw(&contactsprite);
		}

		renderer->Draw(&RadarLine);
	}

	renderer->Draw(&RadarForeground);
}