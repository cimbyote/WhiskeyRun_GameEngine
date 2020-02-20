#ifndef GRAPHICS_OBJECT_BLINN_PHONG
#define GRAPHICS_OBJECT_BLINN_PHONG

#include "GraphicsObject.h"

class GraphicsObject_Blinn_Phong :public GraphicsObject
{
public:
	GraphicsObject_Blinn_Phong(Model *model, ShaderObject *shaderObject, Vect &LightPos, 
			Vect diffuseColor, Vect specularColor, float specularPower = 200.0f);
	GraphicsObject_Blinn_Phong() = delete;
	~GraphicsObject_Blinn_Phong();

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here

	Vect *diffuseColor;
	Vect *specularColor;
	float specularPower;
	Vect *lightPosition;

};
#endif
