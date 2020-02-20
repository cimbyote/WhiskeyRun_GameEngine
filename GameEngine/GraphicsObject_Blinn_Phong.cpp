#include <assert.h>

#include "GraphicsObject_Blinn_Phong.h"
#include "Model.h"

#include "CameraManager.h"

GraphicsObject_Blinn_Phong::GraphicsObject_Blinn_Phong(Model *model, ShaderObject *shaderObject, Vect &LightPos,
			Vect diffuseColor, Vect specularColor, float specularPower)
	: GraphicsObject(model, shaderObject)
{
	this->diffuseColor = new Vect(diffuseColor);
	this->specularColor = new Vect(specularColor);
	this->specularPower = specularPower;
	this->lightPosition = new Vect(LightPos);
}

GraphicsObject_Blinn_Phong::~GraphicsObject_Blinn_Phong()
{
	delete this->diffuseColor;
	delete this->specularColor;
	delete this->lightPosition;
}

void GraphicsObject_Blinn_Phong::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	// Bind the texture
	//GLuint textureID = Texture::Find(this->textName);
	//glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Blinn_Phong::SetDataGPU()
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
	glUniform3fv(this->shaderObject->GetLocation("light_pos"), 1, (float *)&light);

	Vect diffuse = *this->diffuseColor;
	Vect specular= *this->specularColor;
	glUniform3fv(this->shaderObject->GetLocation("diffuse_albedo"), 1, (float *)&diffuse);
	glUniform3fv(this->shaderObject->GetLocation("specular_albedo"), 1, (float *)&specular);
	glUniform1f(this->shaderObject->GetLocation("specular_power"), 20.0f);
}


void GraphicsObject_Blinn_Phong::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Blinn_Phong::RestoreState()
{
	// undo the states you corrupted
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
