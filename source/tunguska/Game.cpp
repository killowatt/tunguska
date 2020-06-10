#include "Game.h"
#include "SDL2/SDL.h"
#include "Input.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);

	Renderer.Initialize(&ResourceSystem);

	CurrentScene = new Scene();
	CurrentScene->Renderer = &Renderer;
	CurrentScene->ResourceManager = &ResourceSystem;

	CurrentScene->Initialize();

	bool running = true;
	while (running)
	{
		Input::ClearKeyState();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat) break;
				Input::keys[event.key.keysym.scancode] = SDL_PRESSED;
				break;
			case SDL_KEYUP:
				if (event.key.repeat) break;
				Input::keys[event.key.keysym.scancode] = SDL_RELEASED;
				break;
			case SDL_MOUSEBUTTONDOWN:
				CurrentScene->OnClick(event.button.x, event.button.y);
				break;
			//case SDL_MOUSEWHEEL:
			//	MouseWheel(event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED);
			//	break;
			}
		}

		Input::Update();

		CurrentScene->Update();
		CurrentScene->Render();

		Renderer.RenderScene();
	}

	ResourceSystem.Shutdown();
	Renderer.Shutdown();

	SDL_Quit();
}