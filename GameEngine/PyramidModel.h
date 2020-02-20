#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include "Model.h"

class PyramidModel : public Model
{
public:
	PyramidModel(const char * const modelFileName);
	virtual ~PyramidModel();

	// tells the compiler do not create or allow it to be used, c++11
	PyramidModel(const PyramidModel &) = delete;
	PyramidModel& operator=(const PyramidModel & other) = delete;

private:
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) override;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) override;



};

#endif