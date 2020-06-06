#include "Switch.h"
#include "Game.h"

void Switch::Initialize(ResourceManager* resourceManager)
{
	SwitchBase = resourceManager->LoadTexture("switchbase.png");
	SwitchUp = resourceManager->LoadTexture("switchup.png");
	SwitchDown = resourceManager->LoadTexture("switchdown.png");

	Bruh.Position = Position;
	Bruh.Size = glm::vec2(32, 64);

	Flicker.SetSize(32, 64);

	Base.SetPosition(Position.x, Position.y);
	Base.SetSize(32, 64);
	Base.Texture = SwitchBase;

	UpdateSwitchState();
}

void Switch::Update()
{
}

void Switch::Render(Renderer* renderer)
{
	renderer->Draw(&Base);
	renderer->Draw(&Flicker);
}

void Switch::OnClick(int32 x, int32 y)
{
	glm::vec4 rec;
	rec.x = Bruh.Position.x;
	rec.y = Bruh.Position.y;
	rec.z = Bruh.Position.x + Bruh.Size.x;
	rec.w = Bruh.Position.y + Bruh.Size.y;

	if (Collision::CheckCollision(glm::vec2(x, y), rec))
	{
		State = !State;
		UpdateSwitchState();
	}
}

void Switch::UpdateSwitchState()
{
	if (!State)
	{
		Flicker.SetPosition(Position.x, Position.y);
		Flicker.Texture = SwitchDown;
	}
	else if (State)
	{
		Flicker.SetPosition(Position.x, Position.y - (32));
		Flicker.Texture = SwitchUp;
	}
}