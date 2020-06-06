#pragma once

#include "Common.h"

class RenderTarget
{
	uint32 FrameBuffer;
	uint32 ColorTexture;

public:
	RenderTarget();
	~RenderTarget();

	void SetResolution(uint32 width, uint32 height);

	uint32 GetFramebufferObject();
	uint32 GetTextureObject();
};