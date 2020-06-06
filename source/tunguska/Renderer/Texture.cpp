#include "Texture.h"

#include "GL/glew.h"

#include <stdio.h>

Texture::Texture()
{
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture()
{
	glDeleteTextures(1, &TextureID);
}

void Texture::SetImage(uint8* pixels, uint32 width, uint32 height)
{
	Width = width;
	Height = height;

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

uint32 Texture::GetTextureID() { return TextureID; }