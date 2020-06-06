#include "Renderer.h"

#include "Sprite.h"

#include "GL/glew.h"




#include "ResourceManager.h"

Renderer::Renderer() 
{
	Window = nullptr;
	Context = nullptr;
}

void Renderer::Initialize(ResourceManager* resourceManager)
{
	Window = SDL_CreateWindow(
		"Tunguska",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	Context = SDL_GL_CreateContext(Window);
	SDL_GL_MakeCurrent(Window, Context);

	glewExperimental = true;
	glewInit();

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SpriteRender = new SpriteRenderer();
	SpriteRender->SetShader(resourceManager->LoadShader("sprite"));
}

void Renderer::Shutdown()
{
	delete SpriteRender;
	SpriteRender = nullptr;

	SDL_GL_DeleteContext(Context);
	SDL_DestroyWindow(Window);
}

void Renderer::Draw(Sprite* sprite)
{
	SpriteRenderQueue.push(sprite);
}

Camera* Renderer::GetCamera()
{
	return &Camera;
}

void Renderer::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	while (!SpriteRenderQueue.empty())
	{
		Sprite* sprite = SpriteRenderQueue.front();
		SpriteRenderQueue.pop();

		SpriteRender->DrawSprite(&Camera, sprite);
	}

	SDL_GL_SwapWindow(Window);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Present()
{
	SDL_GL_SwapWindow(Window);
}

//void Renderer::SetRenderTarget(RenderTarget* renderTarget)
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->GetFramebufferObject());
//}
//
//void Renderer::DrawRenderTarget(RenderTarget* renderTarget)
//{
//}