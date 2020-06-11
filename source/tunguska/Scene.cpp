#include "Scene.h"


#include "Input.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

void Scene::Initialize()
{
	Renderer->GetCamera()->SetSize(glm::vec2(640, 360));

	OurPosition = glm::vec2(0.0f, 0.0f);

	RadarSystem.Position = glm::vec2(640 / 2 - 64, 360 / 2 - 64);
	RadarSystem.Contacts = &Contacts;
	RadarSystem.Initialize(ResourceManager);

	RadarSwitch.Position = glm::vec2(640 / 4, 360 / 3);
	RadarSwitch.Initialize(ResourceManager);

	SecondSwitch.Position = glm::vec2(640 / 4 + 24, 360 / 3);
	SecondSwitch.Initialize(ResourceManager);

	Entities.push_back(&RadarSwitch);
	Entities.push_back(&SecondSwitch);

	Contacts.push_back(ExteriorEntity());
	Contacts.push_back(ExteriorEntity());
	Contacts.push_back(ExteriorEntity());
}

void Scene::Update()
{
	static float ok = 0.0f;
	ok += 0.01f;

	Contacts[0].Position.x = 32 * cos(ok);
	Contacts[0].Position.y = 32 * sin(ok);

	Contacts[1].Position.x = 48 * cos(ok / 8.0f);
	Contacts[1].Position.y = 32 * sin(ok / 6.0f);

	Contacts[2].Position.x = 80 * cos(ok / 2.0f);

	RadarSystem.ScreenIsPowered = RadarSwitch.State;
	RadarSystem.RadarIsPowered = SecondSwitch.State;

	RadarSystem.Update();
}

void Scene::Render()
{
	for (Entity* e : Entities)
	{
		e->Render(Renderer);
	}

	RadarSystem.Render(Renderer);
}

void Scene::OnClick(int32 x, int32 y)
{
	glm::vec2 mouse(x, y);
	glm::vec2 campos = Renderer->GetCamera()->GetPosition();

	mouse = mouse * 0.5f; // downscale to "world" space
	mouse = mouse + campos;

	for (Entity* e : Entities)
	{
		e->OnClick(mouse.x, mouse.y);
	}
}