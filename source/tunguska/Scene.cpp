#include "Scene.h"


#include "Input.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"

void Scene::Initialize()
{
	Renderer->GetCamera()->SetSize(glm::vec2(640, 360));

	OurPosition = glm::vec2(0.0f, 0.0f);
	firstcontact = glm::vec2(32, 42);
	secondcontact = glm::vec2(-16, 25);

	Contacts.push_back(&firstcontact);
	Contacts.push_back(&secondcontact);

	RadarSystem.Position = glm::vec2(640 / 2 - 64, 360 / 2 - 64);
	RadarSystem.Initialize(ResourceManager);

	RadarSwitch.Position = glm::vec2(640 / 4, 360 / 3);
	RadarSwitch.Initialize(ResourceManager);

	SecondSwitch.Position = glm::vec2(640 / 4 + 24, 360 / 3);
	SecondSwitch.Initialize(ResourceManager);

	Entities.push_back(&RadarSwitch);
	Entities.push_back(&SecondSwitch);

	testcontact = new Sprite();
	testcontact->Texture = ResourceManager->LoadTexture("contact.png");
	testcontact->SetSize(4, 4);

	testcontact2 = new Sprite();
	testcontact2->Texture = ResourceManager->LoadTexture("contact.png");
	testcontact2->SetSize(4, 4);

	stationary = new Sprite();
	stationary->Texture = ResourceManager->LoadTexture("contact.png");
	stationary->SetSize(4, 4);

	stationarytarg = glm::vec2(48.0f, 0.0f);

	selectedtarget = new Sprite();
	selectedtarget->Texture = ResourceManager->LoadTexture("select.png");
	selectedtarget->SetSize(8, 8);
}

static float lastepic = 0.0f;
static float epic = 0.0f;
static float timelul = 0.0f;
void Scene::Update()
{
	if (Input::GetKeyDown(SDL_SCANCODE_N))
		nexttarg();

	RadarSystem.ScreenIsPowered = RadarSwitch.State;
	RadarSystem.RadarIsPowered = SecondSwitch.State;

	RadarSystem.Update();

	// RADAR
	//lastepic = epic;
	//if (SecondSwitch.State)
	//	epic += 0.075f;

	//timelul += 0.01f;

	//if (epic > (2 * 3.14159))
	//{
	//	lastepic = epic - lastepic;
	//	epic = 0.0f;
	//}

	//glm::mat4 tf(1.0f);
	//tf = glm::translate(tf, glm::vec3(1280.0f / 2.0f, 720.0f / 2.0f, 0));
	////tf = glm::translate(tf, glm::vec3(128.0f, 128.0f, 0.0f)); un-center
	//tf = glm::rotate(tf, epic, glm::vec3(0.0f, 0.0f, 1.0f));
	//tf = glm::translate(tf, glm::vec3(-128.0f, -128.0f, 0.0f));
	//tf = glm::scale(tf, glm::vec3(256.0f, 256.0f, 1));

	//rdr->SetTransform(tf);


	// CONTACT UPDATE
	//static float angle = 0.0f;
	//angle += 0.001f;

	//firstcontact.x = cos(angle) * 65.0f;
	//firstcontact.y = sin(angle * 1.5f + 0.5f) * 52.0f;

	//secondcontact.x = glm::cos(angle + 1.0f) * 120.0f;
	//secondcontact.y = glm::sin(angle + 3.0f) * 96.0f;

	//fugg(firstcontact, testcontact, lastepic, epic);
	//fugg(secondcontact, testcontact2, lastepic, epic);
	//fugg(stationarytarg, stationary, lastepic, epic);
}

static float radardist = 126.0f;
static float radarscale = 1.0f;

void Scene::fugg(glm::vec2 vec, Sprite* outspr, float lastrdr, float currrdr)
{
	if (glm::distance(glm::vec2(0.0f, 0.0f), vec) > radardist)
		return;


	glm::vec2 right(1.0f, 0.0f);
	glm::vec2 pos = glm::normalize(vec);

	float ang = glm::angle(right, pos);

	if (vec.y < 0.0f) // ourpos y
		ang = 2 * glm::pi<float>() - ang;

	if (ang <= currrdr &&
		ang >= lastrdr)
	{


		float x = vec.x + (1280 / 2.0f);
		float y = vec.y + (720 / 2.0f);

		x *= radarscale;
		y *= radarscale;

		outspr->SetPosition(x, y);

		// selection
		if (targpos && targpos->x == vec.x && targpos->y == vec.y) // lol
			selectedtarget->SetPosition(1280 / 2.0f + targpos->x - 2, 
				720 / 2.0f + targpos->y - 2);
	}
}

void Scene::nexttarg()
{
	static int a = 0;

	a++;
	if (a > 2)
		a = 0;

	switch (a)
	{
	case 0:
		targpos = &firstcontact;
		break;
	case 1:
		targpos = &secondcontact;
		break;
	case 2:
		targpos = &stationarytarg;
		break;
	default:
		targpos = &firstcontact;
		break;
	}
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