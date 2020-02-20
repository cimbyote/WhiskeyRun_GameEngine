#ifndef NULL_MODEL_H
#define NULL_MODEL_H

#include "Model.h"

class NullModel : public Model
{
public:
	NullModel(const char * const modelFileName);
	~NullModel();

	// tells the compiler do not create or allow it to be used, c++11
	NullModel(const NullModel &) = delete;
	NullModel& operator=(const NullModel & other) = delete;

private:
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) override;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) override;
};

#endif