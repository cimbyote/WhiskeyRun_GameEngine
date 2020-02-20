#include <assert.h>

#include "GraphicsObject_TextureLight.h"
#include "Model.h"
#include "TextureManager.h"
#include "CameraManager.h"

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *model, ShaderObject *shaderObject, TextureManager::Name name, Vect LightColor, Vect &LightPos)
	: GraphicsObject(model, shaderObject),
	textureName(name)
{
	this->pLightColor = new Vect(LightColor);
	this->lightPosition = new Vect(LightPos);
	TextureManager::AddUseToTexture(name);
}

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *model, ShaderObject *shaderObject, Vect LightColor)
	: GraphicsObject(model, shaderObject),
	textureName(TextureManager::Name::DEFAULT)
{
	this->pLightColor = new Vect(LightColor);
	this->lightPosition = new Vect(1.0f, 1.0f, 1.0f);
	TextureManager::AddUseToTexture(TextureManager::Name::DEFAULT);
}
GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *model, ShaderObject *shaderObject)
	: GraphicsObject(model, shaderObject),
	textureName(TextureManager::Name::DEFAULT)
{
	this->pLightColor = new Vect(1.0f, 1.0f, 1.0f, 1.0f);
	this->lightPosition = new Vect(1.0f, 1.0f, 1.0f);
	TextureManager::AddUseToTexture(TextureManager::Name::DEFAULT);
}

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *model, ShaderObject *shaderObject, TextureManager::Name name)
	: GraphicsObject(model, shaderObject),
	textureName(name)
{
	this->pLightColor = new Vect(1.0f, 1.0f, 1.0f);
	this->lightPosition = new Vect(0.0f, 1.0, 0.0f);
	TextureManager::AddUseToTexture(name);
}

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete this->pLightColor;
	delete this->lightPosition;
}

void GraphicsObject_TextureLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	GLuint textureID = TextureManager::Find(this->textureName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_TextureLight::SetDataGPU()
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
	glUniformMatrix4fv(this->shaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	Vect light = *this->lightPosition;
	Vect lightColor = *this->pLightColor;
	glUniform3fv(this->shaderObject->GetLocation("vLightPos"), 1, (float *)&light);
	glUniform4fv(this->shaderObject->GetLocation("vColor"), 1, (float *)&lightColor);
}


void GraphicsObject_TextureLight::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_TextureLight::RestoreState()
{
	// undo the states you corrupted
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
