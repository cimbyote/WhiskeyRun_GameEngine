#include <assert.h>

#include "Model.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "CameraManager.h"

GraphicsObject_Wireframe::GraphicsObject_Wireframe(Model *pModel, ShaderObject *shaderObject, Vect color)
	: GraphicsObject(pModel, shaderObject)
{
	assert(pModel);
	assert(shaderObject);

	this->color = new Vect(color);
}

GraphicsObject_Wireframe::~GraphicsObject_Wireframe()
{
	delete this->color;
}

void GraphicsObject_Wireframe::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Wireframe::SetDataGPU()
{
	// use this shader
	this->shaderObject->SetActive();

	// setPosUV the vao
	glBindVertexArray(this->GetModel()->vao);

	// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	Camera *activeCam = CameraManager::GetCurrent();


	Matrix world = this->GetWorld();
	Matrix view = activeCam->getViewMatrix();
	Matrix proj = activeCam->getProjMatrix();

	glUniformMatrix4fv(this->shaderObject->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->shaderObject->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->shaderObject->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	Vect color1 = *this->color;
	glUniform3fv(this->shaderObject->GetLocation("inColor"), 1, (float *)&color1);
}

void GraphicsObject_Wireframe::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Wireframe::RestoreState()
{
	// Restore state
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
