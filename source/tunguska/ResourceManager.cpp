#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <string>

// Texture loader
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* This entire thing sucks


pls fix

*/


Texture* ResourceManager::LoadTexture(const char* fileName)
{
	Texture* texture = nullptr;

	std::string combined = "data/" + std::string(fileName);

	// TODO: handle err

	if (Textures.find(fileName) == Textures.end())
	{
		texture = new Texture();

		int width, height, channels;
		unsigned char* pixels = stbi_load(combined.c_str(),
			&width, &height, &channels, STBI_rgb_alpha);

		if (!pixels)
			printf("oops texture : %s", stbi_failure_reason());

		texture->SetImage(pixels, width, height);

		Textures[fileName] = texture;
	}
	else
	{
		texture = Textures[fileName];
	}

	return texture;
}

std::string ReadFile(std::string fileName)
{
	std::string file;
	std::ifstream fileStream(fileName, std::ios::in);
	if (fileStream.is_open())
	{
		std::string line = "";
		while (getline(fileStream, line))
			file += "\n" + line;
		fileStream.close();
		return file;
	}
	throw std::exception("rip");
}

Shader* ResourceManager::LoadShader(const char* fileName)
{
	Shader* shader = nullptr;

	if (Shaders.find(fileName) == Shaders.end())
	{
		std::string path = "data/" + std::string(fileName);
		std::string vertexPath = path + ".vert";
		std::string pixelPath = path + ".frag";

		std::string vertexSource = ReadFile(vertexPath);
		std::string pixelSource = ReadFile(pixelPath);

		shader = new Shader(vertexSource.c_str(), pixelSource.c_str());
		Shaders[fileName] = shader;
	}
	else
	{
		shader = Shaders[fileName];
	}

	return shader;
}

void ResourceManager::Shutdown()
{
	for (auto pair : Textures)
	{
		Texture* texture = pair.second;
		if (texture) delete texture;

		Textures[pair.first] = nullptr;
	}

	for (auto pair : Shaders)
	{
		Shader* shader = pair.second;
		if (shader) delete shader;

		Shaders[pair.first] = nullptr;
	}
}