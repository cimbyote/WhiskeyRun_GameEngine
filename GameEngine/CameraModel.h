#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Model.h"

class CameraModel : public Model
{
public:
	CameraModel(const char * const modelFileName);
	~CameraModel();

	void update();


	// tells the compiler do not create or allow it to be used, c++11
	CameraModel(const CameraModel &) = delete;
	CameraModel& operator=(const CameraModel & other) = delete;
private:
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) override;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) override;


};

#endif