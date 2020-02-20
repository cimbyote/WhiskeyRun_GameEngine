#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "MathEngine.h"
#include "Camera.h"
#include "CameraNode.h"

class CameraManager
{
	//used to store camera locations as needed
	struct CamValues : Align16
	{
		Vect up;
		Vect camTarget;
		Vect positionVect;

		CamValues()
		{
			up.set(0.0f,0.0f,0.0f);
			camTarget.set(0.0f, 0.0f, 0.0f);
			positionVect.set(0.0f, 0.0f, 0.0f);
		}
	};

public:
	static CameraManager *getManager();

	static void Create();
	static void setUpCameras(int inWidth, int inHeight);
	static void SetCamValues(Camera &inCamera, CamValues inValues);

	static void Add(Camera::Name name, Camera *pCamera);
	void AddToFront(CameraLink *node, CameraLink *&head);
	static Camera * Find(Camera::Name name);
	static void SetCurrent(Camera::Name name);
	static Camera * GetCurrent();

	static void Cull();

	static void UpdateCamera();
	static void UpdateDefaultCamera();

	~CameraManager();
private:

	CameraManager();
	static void privCreate();

	static CameraManager *pCameraManager;

	CamValues *startCamPosition;

	CameraLink *activeCamera;
	Camera *currCamera;
};
#endif