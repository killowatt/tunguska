#include "RenderTarget.h"

#include "GL/glew.h"

RenderTarget::RenderTarget()
{
	resolution = glm::uvec2(0, 0);

	glGenFramebuffers(1, &FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);

	glGenTextures(1, &ColorTexture);
	glBindTexture(GL_TEXTURE_2D, ColorTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, ColorTexture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
	glDeleteTextures(1, &ColorTexture);
	glDeleteFramebuffers(1, &FrameBuffer);
}

void RenderTarget::SetResolution(uint32 width, uint32 height)
{
	resolution = glm::uvec2(width, height);

	glBindTexture(GL_TEXTURE_2D, ColorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, nullptr);
}

glm::uvec2 RenderTarget::GetResolution() { return resolution; }

uint32 RenderTarget::GetFramebufferObject() { return FrameBuffer; }
uint32 RenderTarget::GetTextureID() { return ColorTexture; }