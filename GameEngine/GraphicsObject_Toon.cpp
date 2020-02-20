#include <assert.h>

#include "GraphicsObject_Toon.h"
#include "Model.h"

#include "CameraManager.h"

GraphicsObject_Toon::GraphicsObject_Toon(Model *model, ShaderObject *shaderObject, Vect LightColor, Vect &LightPos)
	: GraphicsObject(model, shaderObject)
{
	this->pLightColor = new Vect(LightColor);
	this->lightPosition = new Vect(LightPos);
}

GraphicsObject_Toon::~GraphicsObject_Toon()
{
	delete this->pLightColor;
	delete this->lightPosition;
}



void GraphicsObject_Toon::SetState()
{
	glActiveTexture(GL_TEXTURE0);
	static const GLubyte toon_tex_data[] =
	{
		0x22, 0x09, 0x00, 0x00,
		0x44, 0x11, 0x00, 0x00,
		0x66, 0x1A, 0x00, 0x00,
		0x88, 0x22, 0x00, 0x00,
		0xCC, 0x44, 0x00, 0x00,
		0xFF, 0x88, 0x00, 0x00
	};

	glGenTextures(1, &tex_toon);
	glBindTexture(GL_TEXTURE_1D, tex_toon);
	glTexStorage1D(GL_TEXTURE_1D, 1, GL_RGB8, sizeof(toon_tex_data) / 4);
	glTexSubImage1D(GL_TEXTURE_1D, 0,
		0, sizeof(toon_tex_data) / 4,
		GL_RGBA, GL_UNSIGNED_BYTE,
		toon_tex_data);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// Bind the texture
	//GLuint textureID = Texture::Find(this->textName);
	//glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Toon::SetDataGPU()
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
	//Vect color = *this->pLightColor;
	glUniform3fv(this->shaderObject->GetLocation("light_pos"), 1, (float *)&light);

	//glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);

}


void GraphicsObject_Toon::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Toon::RestoreState()
{
	// undo the states you corrupted
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
