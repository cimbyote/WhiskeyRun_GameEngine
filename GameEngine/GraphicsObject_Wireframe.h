#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"
//#include "Colors.h"


class GraphicsObject_Wireframe :public GraphicsObject
{
public:
	GraphicsObject_Wireframe(Model *pModel, ShaderObject *shaderObject, Vect color = Vect(1.0f, 1.0f, 1.0f));
	~GraphicsObject_Wireframe();
	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here

	
};
#endif