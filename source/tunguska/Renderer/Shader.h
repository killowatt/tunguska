#pragma once

#include "Common.h"
#include <string>
#include "glm/mat4x4.hpp"

class Shader : NonCopyable
{
private:
public: // temp
	uint32 ShaderProgram;
	bool Valid;

public:
	Shader(const char* vertexSource, const char* pixelSource);
	~Shader();

	bool IsValid();

	void Bind();

	void SetInt(const std::string& name, int32 value);
	void SetFloat(const std::string& name, float value);
	void SetMatrix(const std::string& name, const glm::mat4& value);
};