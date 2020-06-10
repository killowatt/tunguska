#pragma once

#include "Common.h"
#include "glm/vec2.hpp"

class RenderTarget
{
	uint32 FrameBuffer;
	uint32 ColorTexture;

	glm::uvec2 resolution;

public:
	RenderTarget();
	~RenderTarget();

	void SetResolution(uint32 width, uint32 height);
	glm::uvec2 GetResolution();

	uint32 GetFramebufferObject();
	uint32 GetTextureID();
};