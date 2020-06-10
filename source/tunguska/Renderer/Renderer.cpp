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

	spriteRenderer = new SpriteRenderer();
	spriteRenderer->SetCamera(&Camera);
	spriteRenderer->SetShader(resourceManager->LoadShader("sprite"));

	renderTarget = new RenderTarget();
	renderTarget->SetResolution(640, 360);
}

void Renderer::Shutdown()
{

	SDL_GL_DeleteContext(Context);
	SDL_DestroyWindow(Window);
}

void Renderer::Draw(Sprite* sprite)
{
	spriteRenderer->DrawSprite(sprite);
}

Camera* Renderer::GetCamera()
{
	return &Camera;
}

void Renderer::RenderScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->GetFramebufferObject());
	glViewport(0, 0, 640, 360);
	Clear();
	spriteRenderer->Render();


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1280, 720);
	Clear();
	spriteRenderer->DrawRenderTarget(renderTarget);

	Present();
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