#pragma once

#include "Common.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Sprite.h"
#include "Renderer/RenderTarget.h"
#include <queue>

class SpriteRenderer : NonCopyable
{
	uint32 VertexArray;
	uint32 VertexBuffer;
	uint32 TextureCoordinate;

	Camera* SpriteCamera;
	Shader* SpriteShader;

	std::queue<Sprite> SpriteQueue;

public:
	SpriteRenderer();
	~SpriteRenderer();

	void SetCamera(Camera* camera);
	void SetShader(Shader* shader);

	void Begin();
	void DrawSprite(Sprite* sprite);
	void DrawRenderTarget(RenderTarget* renderTarget);
	void Render();
};