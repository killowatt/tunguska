#pragma once

#include "SpriteRenderer.h"
#include "Renderer/RenderTarget.h"
#include "Camera.h"

#include "SDL2/SDL.h"
#include "Common.h"

#include <queue>

class Renderer : NonCopyable
{
private:
	SDL_Window* Window;
	SDL_GLContext Context;

	SpriteRenderer* SpriteRender;

	std::queue<class Sprite*> SpriteRenderQueue;

	Camera Camera;

public:
	Renderer();

	void Initialize(class ResourceManager* resourceManager);
	void Shutdown();

	void Draw(class Sprite* sprite);

	class Camera* GetCamera();

	void RenderScene();

	void Clear();
	void Present();

private:
	//void SetRenderTarget(RenderTarget* renderTarget);
	//void DrawRenderTarget(RenderTarget* renderTarget);
};