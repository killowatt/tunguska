#pragma once

#include "Common.h"
#include "Renderer/Camera.h"

class SpriteRenderer : NonCopyable
{
	uint32 VertexArray;
	uint32 VertexBuffer;
	uint32 TextureCoordinate;

	class Shader* SpriteShader;

public:
	SpriteRenderer();
	~SpriteRenderer();

	void SetShader(class Shader* shader);

	// TODO: begin() so we dont redundantly change state so much
	void DrawSprite(Camera* camera, class Sprite* sprite);
};