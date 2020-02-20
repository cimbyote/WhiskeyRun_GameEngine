#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
// Forward declarations
#include "MathEngine.h"


class Camera final : public Align16
{

public:

	enum class Name
	{
		CAMERA_0,
		CAMERA_1,
		CAMERA_2,
		CAMERA_3,
		CAMERA_4,
		CAMERA_5,
		CAMERA_6,
		MISSINGNO
	};
	struct CameraNorms
	{
		Vect	up;
		Vect	down;
		Vect	forward;
		Vect	backward;
		Vect	right;
		Vect	left;
	};
	struct CameraFrustrum
	{
		float	near_height;
		float	near_width;
		float	far_height;
		float	far_width;

		Vect	nearTopLeft;
		Vect	nearTopRight;
		Vect	nearBottomLeft;
		Vect	nearBottomRight;

		Vect	farTopLeft;
		Vect	farTopRight;
		Vect	farBottomLeft;
		Vect	farBottomRight;
	};
	Camera();
	~Camera();


	Name getName() const;
	void setName(Camera::Name name);

	void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
	void setViewport(const int inX, const int inY, const int width, const int height);
	void setUp_Target_Pos(const Vect &Up_vect, const Vect &inLookAt_pt, const Vect &pos_pt);

	void setTargetObject(GameObject *gameObject, float distance);

	void updateCamera(void);

	Matrix &getViewMatrix();
	Matrix &getProjMatrix();

	void getPos(Vect &outPos) const;
	void getDir(Vect &outDir) const;
	void getUp(Vect &outUp) const;
	void getLookAt(Vect &outLookAt) const;
	void getRight(Vect &outRight) const;

	void getCameraData(Vect &up, Vect &tar, Vect &pos, Vect &upVect, Vect &forward, Vect &pRightNorm);
	void setCameraData(Vect &up, Vect &tar, Vect &pos);

	int getScreenWidth() const;
	int getScreenHeight() const;

	void getFieldOfView(float &Value) const;
	void setFieldOfView(const float Value);

	void getNearDist(float &Value) const;
	void setNearDist(const float Value);

	void getNearTopLeft(Vect &vOut) const;
	void getNearTopRight(Vect &vOut) const;
	void getNearBottomLeft(Vect &vOut) const;
	void getNearBottomRight(Vect &vOut) const;
	void getFarTopLeft(Vect &vOut) const;
	void getFarTopRight(Vect &vOut) const;
	void getFarBottomLeft(Vect &vOut) const;
	void getFarBottomRight(Vect &vOut) const;

	void getCameraNorms(CameraNorms &normOut) const;
	void getCameraFrustrumInfo(CameraFrustrum &infoOut) const;

	// move functions
	void moveCameraForward();
	void moveCameraBack();
	void panCameraLeft();
	void panCameraRight();
	void panCameraUp();
	void panCameraDown();
	void rotateLeftAroundTarget();
	void rotateRightAroundTarget();
	void spinCamLeft();
	void spinCamRight();

	void resetCamera();


private:  
	void privSetViewState(void);
	void privCalcPlaneHeightWidth(void);
	void privCalcFrustumVerts(void);
	void privCalcFrustumCollisionNormals(void);
	void privUpdateProjectionMatrix(void);
	void privUpdateViewMatrix(void);


private:  

	struct CameraPerspective
	{
		float nearDist;
		float farDist;
		float fovy;
		float aspectRatio;
	};

	struct CameraViewport
	{
		int	x;
		int	y;
		int	width;
		int height;
	};


	

	struct CameraVectors
	{
		Vect	up;
		Vect	forward;
		Vect	right;
	};

	CameraPerspective camPersp;
	CameraViewport camViewport;
	CameraFrustrum camFrustrum;
	CameraNorms camNorms;
	CameraVectors camVects;

	Matrix	projMatrix;
	Matrix	viewMatrix;

	Vect	camPosition;
	Vect	camTarget;

	Camera::Name name;

	char pad[12];

};

#endif