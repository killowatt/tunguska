#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

#include <unordered_map>

class ResourceManager
{
private:
	std::unordered_map<std::string, Texture*> Textures;
	std::unordered_map<std::string, Shader*> Shaders;

public:
	Texture* LoadTexture(const char* fileName);
	Shader* LoadShader(const char* fileName);

	void Shutdown();
};