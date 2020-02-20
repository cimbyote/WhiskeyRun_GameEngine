#include <assert.h>
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject_ColorByPosition.h"
#include "CameraManager.h"

GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(Model *model, ShaderObject *shaderObject)
	: GraphicsObject(model, shaderObject)
{
	assert(pModel);
	assert(shaderObject);
}

void GraphicsObject_ColorByPosition::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ColorByPosition::SetDataGPU()
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
}

void GraphicsObject_ColorByPosition::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ColorByPosition::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}