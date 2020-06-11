#include "SpriteRenderer.h"

#include "Sprite.h"
#include "Texture.h"
#include "Shader.h"

#include "GL/glew.h"

#include "glm/gtc/matrix_transform.hpp"

const float VertexData[] =
{
	0, 1,
	1, 0,
	0, 0,
	0, 1,
	1, 1,
	1, 0
};
const float TexCoordData[] =
{
	0, 1,
	1, 0,
	0, 0,
	0, 1,
	1, 1,
	1, 0
};

SpriteRenderer::SpriteRenderer()
{
	glGenVertexArrays(1, &VertexArray);
	glGenBuffers(1, &VertexBuffer);
	glGenBuffers(1, &TextureCoordinate);

	glBindVertexArray(VertexArray);

	static const uint32 VERTEX_INDEX = 0;
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_INDEX, 2, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(VERTEX_INDEX);

	static const uint32 TEXCOORD_INDEX = 1;
	glBindBuffer(GL_ARRAY_BUFFER, TextureCoordinate);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoordData), TexCoordData, GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORD_INDEX, 2, GL_FLOAT, false, 0, 0);
	glEnableVertexAttribArray(TEXCOORD_INDEX);

	glBindVertexArray(0);
}
SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(1, &VertexBuffer);
	glDeleteBuffers(1, &TextureCoordinate);
	glDeleteVertexArrays(1, &VertexArray);
}

void SpriteRenderer::SetCamera(Camera* camera)
{
	SpriteCamera = camera;
}
void SpriteRenderer::SetShader(Shader* shader)
{
	SpriteShader = shader;
}

void SpriteRenderer::Begin()
{

}

void SpriteRenderer::DrawSprite(Sprite* sprite)
{
	SpriteQueue.push(*sprite);
}

void SpriteRenderer::DrawRenderTarget(RenderTarget* renderTarget)
{
	glUseProgram(SpriteShader->ShaderProgram);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));

	SpriteShader->SetMatrix("projection", glm::mat4(1.0f));
	SpriteShader->SetMatrix("view", glm::mat4(1.0f));
	SpriteShader->SetMatrix("model", model);
	SpriteShader->SetInt("sprite", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTarget->GetTextureID());

	glBindVertexArray(VertexArray);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void SpriteRenderer::Render()
{
	glUseProgram(SpriteShader->ShaderProgram);

	SpriteShader->SetMatrix("projection", SpriteCamera->GetProjection());
	SpriteShader->SetMatrix("view", SpriteCamera->GetView());
	SpriteShader->SetInt("sprite", 0);

	glBindVertexArray(VertexArray);

	while (!SpriteQueue.empty())
	{
		Sprite* sprite = &SpriteQueue.front();

		SpriteShader->SetMatrix("model", sprite->GetTransform());
		SpriteShader->SetFloat("opacity", sprite->Opacity);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite->Texture->GetTextureID());

		glDrawArrays(GL_TRIANGLES, 0, 6);

		SpriteQueue.pop();
	}

	glBindVertexArray(0);
}