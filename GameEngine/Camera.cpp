#include <assert.h>
#include <math.h>

#include "sb7.h"

#include "MathEngine.h"
#include "Camera.h"
#include "Config.h"

Camera::Camera()
{
	camTarget.set(0.0f,0.0f,0.0f);
	this->name = Camera::Name::MISSINGNO;
}

Camera::~Camera()
{

}
/***
*     _____                   _____      _
*    /  __ \                 /  ___|    | |
*    | /  \/ __ _ _ __ ___   \ `--.  ___| |_ _   _ _ __
*    | |    / _` | '_ ` _ \   `--. \/ _ \ __| | | | '_ \
*    | \__/\ (_| | | | | | | /\__/ /  __/ |_| |_| | |_) |
*     \____/\__,_|_| |_| |_| \____/ \___|\__|\__,_| .__/
*                                                 | |
*                                                 |_|
*/
void Camera::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
{
	this->camPersp.aspectRatio = Aspect;
	this->camPersp.fovy = Fovy;
	this->camPersp.nearDist = NearDist;
	this->camPersp.farDist = FarDist;
}

int Camera::getScreenWidth() const
{
	return this->camViewport.width;
}

int Camera::getScreenHeight() const
{
	return this->camViewport.height;
}

void Camera::setViewport(const int inX, const int inY, const int width, const int height)
{
	this->camViewport.x = inX;
	this->camViewport.y = inY;
	this->camViewport.width = width;
	this->camViewport.height = height;

	this->privSetViewState();
};


// Simple wrapper
void Camera::privSetViewState(void)
{
	glViewport(this->camViewport.x, this->camViewport.y, this->camViewport.width, this->camViewport.height);
};


// Goal, calculate the near height / width, same for far plane 
void Camera::privCalcPlaneHeightWidth(void)
{

	this->camFrustrum.near_height = 2.0f * tanf((this->camPersp.fovy * MATH_PI / 180.0f) * .5f) * this->camPersp.nearDist;
	this->camFrustrum.near_width = this->camFrustrum.near_height * this->camPersp.aspectRatio;

	this->camFrustrum.far_height = 2.0f * tanf((this->camPersp.fovy * MATH_PI / 180.0f) * .5f) * this->camPersp.farDist;
	this->camFrustrum.far_width = this->camFrustrum.far_height * this->camPersp.aspectRatio;

};


void Camera::getCameraData(Vect &up, Vect &tar, Vect &pos, Vect &inUpNorm, Vect &inForwardNorm, Vect &pRightNorm)
{
	getPos(pos);
	getLookAt(tar);
	getUp(inUpNorm);
	up = pos + inUpNorm;

	inForwardNorm = tar - pos;
	inForwardNorm.norm();

	getRight(pRightNorm);
}

void Camera::setCameraData(Vect &up, Vect &tar, Vect &pos)
{
	Vect upVectTemp = up - pos;
	setUp_Target_Pos(upVectTemp, tar, pos);
}

void Camera::setUp_Target_Pos(const Vect &inUp, const Vect &inLookAt, const Vect &inPos)
{
	// Remember the up, lookAt and right are unit, and are perpendicular.
	// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
	// Make sure that all vectors are unit vectors.

	this->camTarget = inLookAt;

	// Point out of the screen into your EYE
	this->camVects.forward = inPos - inLookAt;
	this->camVects.forward.norm();

	// Clean up the vectors (Right hand rule)
	this->camVects.right = inUp.cross(this->camVects.forward);
	this->camVects.right.norm();

	this->camVects.up = this->camVects.forward.cross(this->camVects.right);
	this->camVects.up.norm();

	this->camPosition = inPos;
};
void Camera::setTargetObject(GameObject* gameObject, float distance)
{
	setUp_Target_Pos(Vect(0.0f, 1.0f, 0.0f), *gameObject->GetPosition(), Vect(gameObject->GetPosition()->x(), gameObject->GetPosition()->y(), distance));
}

void Camera::privCalcFrustumVerts(void)
{
	// Top Left corner and so forth.  In this form to see the pattern
	// Might be confusing (remember the picture) forwardVect goes from screen into your EYE
	// so distance from the eye is "negative" forwardVect
	this->camFrustrum.nearTopLeft = this->camPosition - this->camVects.forward * this->camPersp.nearDist + this->camVects.up * this->camFrustrum.near_height * 0.5f - this->camVects.right * this->camFrustrum.near_width * 0.5f;
	this->camFrustrum.nearTopRight = this->camPosition - this->camVects.forward * this->camPersp.nearDist + this->camVects.up * this->camFrustrum.near_height * 0.5f + this->camVects.right * this->camFrustrum.near_width * 0.5f;
	this->camFrustrum.nearBottomLeft = this->camPosition - this->camVects.forward * this->camPersp.nearDist - this->camVects.up * this->camFrustrum.near_height * 0.5f - this->camVects.right * this->camFrustrum.near_width * 0.5f;
	this->camFrustrum.nearBottomRight = this->camPosition - this->camVects.forward * this->camPersp.nearDist - this->camVects.up * this->camFrustrum.near_height * 0.5f + this->camVects.right * this->camFrustrum.near_width * 0.5f;
	this->camFrustrum.farTopLeft = this->camPosition - this->camVects.forward * this->camPersp.farDist + this->camVects.up * this->camFrustrum.far_height * 0.5f - this->camVects.right * this->camFrustrum.far_width * 0.5f;
	this->camFrustrum.farTopRight = this->camPosition - this->camVects.forward * this->camPersp.farDist + this->camVects.up * this->camFrustrum.far_height * 0.5f + this->camVects.right * this->camFrustrum.far_width * 0.5f;
	this->camFrustrum.farBottomLeft = this->camPosition - this->camVects.forward * this->camPersp.farDist - this->camVects.up * this->camFrustrum.far_height * 0.5f - this->camVects.right * this->camFrustrum.far_width * 0.5f;
	this->camFrustrum.farBottomRight = this->camPosition - this->camVects.forward * this->camPersp.farDist - this->camVects.up * this->camFrustrum.far_height * 0.5f + this->camVects.right * this->camFrustrum.far_width * 0.5f;
};

void Camera::privCalcFrustumCollisionNormals(void)
{
	// Normals of the frustum around nearTopLeft
	Vect A = this->camFrustrum.nearBottomLeft - this->camFrustrum.nearTopLeft;
	Vect B = this->camFrustrum.nearTopRight - this->camFrustrum.nearTopLeft;
	Vect C = this->camFrustrum.farTopLeft - this->camFrustrum.nearTopLeft;

	this->camNorms.forward = A.cross(B);
	this->camNorms.forward.norm();

	this->camNorms.left = C.cross(A);
	this->camNorms.left.norm();

	this->camNorms.up = B.cross(C);
	this->camNorms.up.norm();

	// Normals of the frustum around farBottomRight
	A = this->camFrustrum.farBottomLeft - this->camFrustrum.farBottomRight;
	B = this->camFrustrum.farTopRight - this->camFrustrum.farBottomRight;
	C = this->camFrustrum.nearBottomRight - this->camFrustrum.farBottomRight;

	this->camNorms.backward = A.cross(B);
	this->camNorms.backward.norm();

	this->camNorms.right = B.cross(C);
	this->camNorms.right.norm();

	this->camNorms.down = C.cross(A);
	this->camNorms.down.norm();
};

/***
*    ___  ___                                    _
*    |  \/  |                                   | |
*    | .  . | _____   _____ _ __ ___   ___ _ __ | |_
*    | |\/| |/ _ \ \ / / _ \ '_ ` _ \ / _ \ '_ \| __|
*    | |  | | (_) \ V /  __/ | | | | |  __/ | | | |_
*    \_|  |_/\___/ \_/ \___|_| |_| |_|\___|_| |_|\__|
*
*
*/
void Camera::moveCameraForward()
{
	camPosition = camPosition - camMoveSpeed * camNorms.forward;
	camTarget = camTarget - camMoveSpeed * camNorms.forward;
}
void Camera::moveCameraBack()
{
	camPosition = camPosition + camMoveSpeed * camNorms.forward;
	camTarget = camTarget + camMoveSpeed * camNorms.forward;
}
void Camera::panCameraLeft()
{
	Vect moveBy(camTurnSpeed, 0, 0);
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);
	
	camTarget += moveBy;

	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::panCameraRight()
{
	Vect moveBy(camTurnSpeed, 0, 0);
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);
	
	camTarget -= moveBy;

	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::panCameraUp()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	Matrix Trans(TRANS, camTarget);
	Matrix NegTrans(TRANS, -camTarget);

	Matrix Rot;
	Rot.set(RotAxisAngleType::ROT_AXIS_ANGLE, camNorms.right, -camTurnSpeed);

	Matrix M = NegTrans * Rot * Trans;

	camVects.up = camVects.up * M;
	camPosition = camPosition * M;
	camTarget = camTarget * M;

	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::panCameraDown()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	Matrix Trans(TRANS, camTarget);
	Matrix NegTrans(TRANS, -camTarget);

	Matrix Rot;
	Rot.set(RotAxisAngleType::ROT_AXIS_ANGLE, camNorms.right, camTurnSpeed);

	Matrix M = NegTrans * Rot * Trans;

	camVects.up = camVects.up * M;
	camPosition = camPosition * M;
	camTarget = camTarget * M;
	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::rotateLeftAroundTarget()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	Matrix Trans(TRANS, camTarget);
	Matrix NegTrans(TRANS, -camTarget);

	Matrix Rot;
	Rot.set(RotAxisAngleType::ROT_AXIS_ANGLE, camNorms.up, -camTurnSpeed);

	Matrix M = NegTrans * Rot * Trans;

	camVects.up = camVects.up * M;
	camPosition = camPosition * M;
	camTarget = camTarget * M;

	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::rotateRightAroundTarget()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	Matrix Trans(TRANS, camTarget);
	Matrix NegTrans(TRANS, -camTarget);

	Matrix Rot;
	Rot.set(RotAxisAngleType::ROT_AXIS_ANGLE,camNorms.up, camTurnSpeed);
	//Rot.set();

	Matrix M = NegTrans * Rot * Trans;

	camVects.up = camVects.up * M;
	camPosition = camPosition * M;
	camTarget = camTarget * M;

	this->setCameraData(camVects.up, camTarget, camPosition);
}

void Camera::spinCamLeft()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	camPosition = camPosition - camTurnSpeed * camNorms.right;
	camTarget = camTarget - camTurnSpeed * camNorms.right;


	this->setCameraData(camVects.up, camTarget, camPosition);
}
void Camera::spinCamRight()
{
	this->getCameraData(camVects.up, camTarget, camPosition, camNorms.up, camNorms.forward, camNorms.right);

	camPosition = camPosition + camTurnSpeed * camNorms.right;
	camTarget = camTarget + camTurnSpeed * camNorms.right;


	this->setCameraData(camVects.up, camTarget, camPosition);
}

void Camera::resetCamera()
{
	this->setUp_Target_Pos(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 4.5f));
}


/***
*     _   _           _       _
*    | | | |         | |     | |
*    | | | |_ __   __| | __ _| |_ ___
*    | | | | '_ \ / _` |/ _` | __/ _ \
*    | |_| | |_) | (_| | (_| | ||  __/
*     \___/| .__/ \__,_|\__,_|\__\___|
*          | |
*          |_|
*/


// The projection matrix (note it's invertable)
void Camera::privUpdateProjectionMatrix(void)
{
	this->projMatrix[m0] = 2.0f * this->camPersp.nearDist / this->camFrustrum.near_width;
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f * this->camPersp.nearDist / this->camFrustrum.near_height;
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = (this->camPersp.farDist + this->camPersp.nearDist) / (this->camPersp.nearDist - this->camPersp.farDist);
	this->projMatrix[m11] = -1.0f;

	this->projMatrix[m12] = 0.0f;
	this->projMatrix[m13] = 0.0f;
	this->projMatrix[m14] = (2.0f * this->camPersp.farDist * this->camPersp.nearDist) / (this->camPersp.nearDist - this->camPersp.farDist);
	this->projMatrix[m15] = 0.0f;
};


void Camera::privUpdateViewMatrix(void)
{
	// This functions assumes the your upVect, rightVect, forwardVect are still unit
	// And perpendicular to each other
	//  view = Rot(orient) * trans(-(eye.basis) )

	this->viewMatrix[m0] = this->camVects.right[x];
	this->viewMatrix[m1] = this->camVects.up[x];
	this->viewMatrix[m2] = this->camVects.forward[x];
	this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->camVects.right[y];
	this->viewMatrix[m5] = this->camVects.up[y];
	this->viewMatrix[m6] = this->camVects.forward[y];
	this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8] = this->camVects.right[z];
	this->viewMatrix[m9] = this->camVects.up[z];
	this->viewMatrix[m10] = this->camVects.forward[z];
	this->viewMatrix[m11] = 0.0f;

	// Change of basis (dot with the basis vectors)
	this->viewMatrix[m12] = -camPosition.dot(camVects.right);
	this->viewMatrix[m13] = -camPosition.dot(camVects.up);
	this->viewMatrix[m14] = -camPosition.dot(camVects.forward);
	this->viewMatrix[m15] = 1.0f;
};


// Update everything (make sure it's consistent)
void Camera::updateCamera(void)
{

	// First find the near height/width, far height/width
	this->privCalcPlaneHeightWidth();

	// Find the frustum physical verts
	this->privCalcFrustumVerts();

	// find the frustum collision normals
	this->privCalcFrustumCollisionNormals();

	// update the projection matrix
	this->privUpdateProjectionMatrix();

	// update the view matrix
	this->privUpdateViewMatrix();
}

/***
*     _____      _                     _   _____      _
*    /  ___|    | |                   | | |  __ \    | |
*    \ `--.  ___| |_    __ _ _ __   __| | | |  \/ ___| |_ ___
*     `--. \/ _ \ __|  / _` | '_ \ / _` | | | __ / _ \ __/ __|
*    /\__/ /  __/ |_  | (_| | | | | (_| | | |_\ \  __/ |_\__ \
*    \____/ \___|\__|  \__,_|_| |_|\__,_|  \____/\___|\__|___/
*
*
*/

Camera::Name Camera::getName() const
{
	return this->name;
}
void Camera::setName(Camera::Name inName)
{
	this->name = inName;
}

Matrix & Camera::getViewMatrix(void)
{
	return this->viewMatrix;
}

Matrix & Camera::getProjMatrix(void)
{
	return this->projMatrix;
}

void Camera::getPos(Vect &outPos) const
{
	outPos = this->camPosition;
}

void  Camera::getDir(Vect &outDir) const
{
	outDir = this->camVects.forward;
}

void  Camera::getUp(Vect &outUp) const
{
	outUp = this->camVects.up;
}

void Camera::getLookAt(Vect &outLookAt) const
{
	outLookAt = this->camTarget;
}

void Camera::getRight(Vect &outRight) const
{
	outRight = this->camVects.right;
}

void Camera::getFieldOfView(float &Value) const
{
	Value = this->camPersp.fovy;
};

void Camera::setFieldOfView(const float Value)
{
	this->camPersp.fovy = Value;
};

void Camera::getNearDist(float &Value) const
{
	Value = this->camPersp.nearDist;
}

void Camera::setNearDist(const float Value)
{
	this->camPersp.nearDist = Value;
}

void Camera::getNearTopLeft(Vect &vOut) const
{
	vOut = this->camFrustrum.nearTopLeft;
}
void Camera::getNearTopRight(Vect &vOut) const
{
	vOut = this->camFrustrum.nearTopRight;
}
void Camera::getNearBottomLeft(Vect &vOut)const
{
	vOut = this->camFrustrum.nearBottomLeft;
}
void Camera::getNearBottomRight(Vect &vOut) const
{
	vOut = this->camFrustrum.nearBottomRight;
}
void Camera::getFarTopLeft(Vect &vOut) const
{
	vOut = this->camFrustrum.farTopLeft;
}
void Camera::getFarTopRight(Vect &vOut) const
{
	vOut = this->camFrustrum.farTopRight;
}
void Camera::getFarBottomLeft(Vect &vOut) const
{
	vOut = this->camFrustrum.farBottomLeft;
}
void Camera::getFarBottomRight(Vect &vOut)const
{
	vOut = this->camFrustrum.farBottomRight;
}

void Camera::getCameraNorms(CameraNorms &normOut) const
{
	normOut = this->camNorms;
}

void Camera::getCameraFrustrumInfo(CameraFrustrum &infoOut) const
{
	infoOut = this->camFrustrum;
}