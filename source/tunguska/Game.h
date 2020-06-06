#pragma once

#include "Common.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"

class Game
{
public:
	Game();

	Renderer Renderer;
	ResourceManager ResourceSystem;

	Scene* CurrentScene;
};