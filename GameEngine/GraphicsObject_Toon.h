#ifndef GRAPHICS_OBJECT_TOON
#define GRAPHICS_OBJECT_TOON

#include "GraphicsObject.h"


class GraphicsObject_Toon :public GraphicsObject
{
public:
	GraphicsObject_Toon(Model *model, ShaderObject *shaderObject, Vect LightColor, Vect &LightPos);
	GraphicsObject_Toon() = delete;
	~GraphicsObject_Toon();


	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here

	GLuint          tex_toon;

	Vect *pLightColor;
	Vect *lightPosition;

};
#endif
