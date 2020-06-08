#include "Scene.h"



#include "glm/gtc/matrix_transform.hpp"

void Scene::Initialize()
{
	OurPosition = glm::vec2(0.0f, 0.0f);
	firstcontact = glm::vec2(32, 42);
	secondcontact = glm::vec2(-16, 25);

	Contacts.push_back(&firstcontact);
	Contacts.push_back(&secondcontact);




	RadarSwitch.Position = glm::vec2(1280 / 4, 720 / 3);
	RadarSwitch.Initialize(ResourceManager);

	SecondSwitch.Position = glm::vec2(1280 / 4 + 48, 720 / 3);
	SecondSwitch.Initialize(ResourceManager);

	Entities.push_back(&RadarSwitch);
	Entities.push_back(&SecondSwitch);

	rdr = new Sprite();
	rdr->Texture = ResourceManager->LoadTexture("radar.png");

	radarscreen = new Sprite();
	radarscreen->Texture = ResourceManager->LoadTexture("radarscreen.png");
	radarscreen->SetSize(256, 256);
	radarscreen->SetPosition(1280 / 2 - 128, 720 / 2 - 128);

	radarcover = new Sprite();
	radarcover->Texture = ResourceManager->LoadTexture("radarcover.png");
	radarcover->SetSize(256, 256);
	radarcover->SetPosition(1280 / 2 - 128, 720 / 2 - 128);

	testcontact = new Sprite();
	testcontact->Texture = ResourceManager->LoadTexture("contact.png");
	testcontact->SetSize(8, 8);
}

static float lastepic = 0.0f;
static float epic = 0.0f;
static float timelul = 0.0f;
void Scene::Update()
{
	lastepic = epic;
	if (SecondSwitch.State)
		epic += 0.075f;

	timelul += 0.01f;

	if (epic > (2 * 3.14159))
	{
		lastepic = epic - lastepic;
		epic = 0.0f;
	}

	glm::mat4 tf(1.0f);
	tf = glm::translate(tf, glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f, 0));
	//tf = glm::translate(tf, glm::vec3(128.0f, 128.0f, 0.0f)); un-center
	tf = glm::rotate(tf, epic, glm::vec3(0.0f, 0.0f, 1.0f));
	tf = glm::translate(tf, glm::vec3(-128.0f, -128.0f, 0.0f));
	tf = glm::scale(tf, glm::vec3(256.0f, 256.0f, 1));

	//tf = glm::translate(tf, glm::vec3(1280 / 1.75f, 720 / 3 + 64, 0));
	//tf = glm::translate(tf, glm::vec3(0.5 * 200, 0.5 * 200, 0.0f));
	//tf = glm::rotate(tf, epic, glm::vec3(0.0f, 0.0f, 1.0f));
	//tf = glm::scale(tf, glm::vec3(200, 200, 1));

	rdr->SetTransform(tf);
	//rdr->SetPosition(1280 / 2, 720 / 2);
	//rdr->SetSize(128, 128);

	contac.angle += 0.001f;
	contac.dist = 64 + 32 * sin(timelul / 48.0f);

	if (contac.angle > (2 * 3.14159))
	{
		contac.angle = 0.0f;
	}
	//contac.dist = 48.0f + sin(epic) * 3.0f;

	if (SecondSwitch.State &&
		contac.angle <= epic &&
		contac.angle >= lastepic)
	{
		printf("PING\n");

		float relativex = contac.dist * cos(contac.angle);
		float relativey = contac.dist * sin(contac.angle);


		
		testcontact->SetPosition(relativex + (1280 / 2.0f),
			relativey + (720 / 2.0f));
	}


	if (SecondSwitch.State)
		printf("RDR: %f CON: %f\n", epic, contac.angle);
}

void Scene::Render()
{
	Renderer->Draw(radarscreen);

	if (RadarSwitch.State)
		Renderer->Draw(rdr);

	if (RadarSwitch.State)
		Renderer->Draw(testcontact);

	for (Entity* e : Entities)
	{
		e->Render(Renderer);
	}

	Renderer->Draw(radarcover);
}

void Scene::OnClick(int32 x, int32 y)
{
	glm::vec2 mouse(x, y);
	glm::vec2 campos = Renderer->GetCamera()->GetPosition();

	mouse = mouse + campos;

	for (Entity* e : Entities)
	{
		e->OnClick(mouse.x, mouse.y);
	}
}