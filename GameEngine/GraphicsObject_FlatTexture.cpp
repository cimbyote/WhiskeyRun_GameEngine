#include <assert.h>

#include "GraphicsObject_FlatTexture.h"
#include "TextureManager.h"
#include "Model.h"
#include "CameraManager.h"

GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(Model *model, ShaderObject *shaderObject, TextureManager::Name name)
	: GraphicsObject(model, shaderObject), textureName(name)
{
	TextureManager::AddUseToTexture(name);
}

void GraphicsObject_FlatTexture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = TextureManager::Find(this->textureName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_FlatTexture::SetDataGPU()
{
	// use this shader
	this->shaderObject->SetActive();

	// setPosUV the vao
	glBindVertexArray(this->GetModel()->vao);

	Camera *activeCam = CameraManager::GetCurrent();


	Matrix world = this->GetWorld();
	Matrix view = activeCam->getViewMatrix();
	Matrix proj = activeCam->getProjMatrix();

	glUniformMatrix4fv(this->shaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->shaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->shaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);;
}

void GraphicsObject_FlatTexture::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
