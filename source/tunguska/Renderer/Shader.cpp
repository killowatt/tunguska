#include "Shader.h"
#include "GL/glew.h"

#include "Texture.h"

Shader::Shader(const char* vertexSource, const char* pixelSource)
{
	int result = 0;
	Valid = false;

	uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	result = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		Log::Warning("Vertex shader failed to compile");
		return;
	}

	uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &pixelSource, nullptr);
	glCompileShader(fragmentShader);

	result = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		Log::Warning("Fragment shader failed to compile");
		return;
	}

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	result = 0;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		Log::Warning("Shader linking failed");
		return;
	}

	Valid = true;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(ShaderProgram);
	Valid = false;
}

bool Shader::IsValid() { return Valid; }

void Shader::Bind()
{
	glUseProgram(ShaderProgram);
}

void Shader::SetInt(const std::string& name, int32 value)
{
	uint32 location = glGetUniformLocation(ShaderProgram, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	uint32 location = glGetUniformLocation(ShaderProgram, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetMatrix(const std::string& name, const glm::mat4& value)
{
	uint32 location = glGetUniformLocation(ShaderProgram, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
