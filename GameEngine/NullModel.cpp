#include <sb7.h>
#include <assert.h>

#include "NullModel.h"


NullModel::NullModel(const char * const modelFileName)
	: Model()
{
	shutUp(modelFileName);
}

NullModel::~NullModel()
{
	// remove anything dynamic here
}

void NullModel::createVAO(Model::ModelType type, const char * const modelFileName, int textureNumber)
{
	shutUp(type);
	shutUp(modelFileName);
	shutUp(textureNumber);
}

void NullModel::createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName)
{
	shutUp(type);
	shutUp(pModelFileName);
	shutUp(objectName);
}