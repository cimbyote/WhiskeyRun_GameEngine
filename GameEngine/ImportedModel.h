#ifndef IMPORTED_MODEL_H
#define IMPORTED_MODEL_H

#include "Model.h"
#include "GraphicsObject_TextureLight.h"
#include "ShaderObject.h"

class ImportedModel : public Model
{
public:
	ImportedModel(Model::ModelType type, const char * const pModelFileName, int textureNumber);

	ImportedModel() = delete;
	ImportedModel(const ImportedModel &) = delete;
	ImportedModel & operator = (ImportedModel &) = delete;
	virtual ~ImportedModel();

	float centerX;
	float centerY;
	float centerZ;
	float radius;

private:
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) override;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) override;

};

#endif