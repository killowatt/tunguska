#pragma once

#include "Common.h"

class Texture : NonCopyable
{
private:
	uint32 TextureID;

	uint32 Width;
	uint32 Height;

public:
	Texture();
	~Texture();

	void SetImage(uint8* pixels, uint32 width, uint32 height);

	uint32 GetTextureID();
};
