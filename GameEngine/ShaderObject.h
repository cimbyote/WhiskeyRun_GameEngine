#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <sb7.h>

class ShaderObject
{
public:
	enum Name
	{
		NULL_SHADER,
		COLOR_LIGHT,
		TEXTURE_SIMPLE,
		TEXTURE_POINT_LIGHT,
		BLINN_PHONG,
		TOON
	};

public:
	ShaderObject(ShaderObject::Name shaderName, const char * const pShaderBaseFileName);

	ShaderObject() = delete;
	ShaderObject(const ShaderObject &) = delete;
	ShaderObject &operator = (ShaderObject &) = delete;
	virtual ~ShaderObject() = default;

	void SetActive();
	GLint GetLocation(const char * pUniformName);

private:
	bool privCreateShader(GLuint &programObject, const char * const pShaderBaseFileName);
	bool privLoadNCompile(GLuint &shaderObject, const char * const pShaderFileName, GLenum shader_type);

public:
	Name	name;
	GLuint	programObject;

};

#endif