#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"


class Model;

class RenderMaterial
{
protected:
	virtual void SetState() = 0;
	virtual void SetDataGPU() = 0;
	virtual void Draw() = 0;
	virtual void RestoreState() = 0;

};

class GraphicsObject : private RenderMaterial
{
public:
	GraphicsObject(Model *model, ShaderObject *shaderObject);

	GraphicsObject() = delete;
	virtual ~GraphicsObject();

	void Render();
	void SetWorld(Matrix &_world);

	Model *GetModel() const;
	Matrix &GetWorld();

	void SetColor(Vect color);

protected:
	Model			*pModel;
	Matrix			*pWorld;
	ShaderObject	*shaderObject;

	Vect *color;

};

#endif