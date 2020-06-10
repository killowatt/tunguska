#pragma once

#include "Common.h"
#include "Renderer/Camera.h"
#include "Renderer/RenderTarget.h"
#include "Renderer/SpriteRenderer.h"
#include "SDL2/SDL.h"

class Renderer : NonCopyable
{
private:
	SDL_Window* Window;
	SDL_GLContext Context;

	SpriteRenderer* spriteRenderer;

	Camera Camera;

	RenderTarget* renderTarget;

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