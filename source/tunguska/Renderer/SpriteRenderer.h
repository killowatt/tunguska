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

	void DrawSprite(Camera* camera, class Sprite* sprite);
};