#include <assert.h>
#include <math.h>

#include "MathEngine.h"
#include "GameObject.h"
#include "GameObjectAnim.h"
#include "GraphicsObject.h"
#include "AnimationController.h"
//#include "FrameBucket.h"

//extern Frame_Bucket *pHead;

GameObjectAnim::GameObjectAnim(GraphicsObject  *graphicsObject)
	: GameObject(graphicsObject)
{
	assert(graphicsObject != 0);

	this->pDof = new Vect(0.0f, 0.0f, 0.0f);
	assert(pDof);

	this->pUp = new Vect(0.0f, 1.0f, 0.0f);
	assert(pUp);

	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(pScale);

	this->pPos = new Vect(0.0f, 0.0f, 0.0f);
	assert(pPos);

	this->indexBoneArray = 0;

	this->pLocal = new Matrix(IDENTITY);
	assert(pLocal);

	this->pBoneOrientation = new Matrix(IDENTITY);
	assert(pBoneOrientation);

	this->deltaSpinX = 0.0f;
	this->deltaSpinY = 0.0f;
	this->deltaSpinZ = 0.0f;
}

Matrix GameObjectAnim::GetBoneOrientation(void) const
{
	return Matrix(*this->pBoneOrientation);
}

void GameObjectAnim::SetBoneOrientation(const Matrix &tmp)
{
	*this->pBoneOrientation = tmp;
}

void GameObjectAnim::SetIndex(int val)
{
	this->indexBoneArray = val;
}

GameObjectAnim::~GameObjectAnim()
{
	//delete this->pWorld;
}

void GameObjectAnim::Update(Time)
{
	GameObject *pBoneParent = (GameObject *)this->GetParent();
	assert(pBoneParent != 0);

	Matrix ParentWorld = *pBoneParent->GetWorld();

	// REMEMBER this is for Animation and hierachy, you need to handle models differently
	// Get the result bone array, from there make the matrix
	FrameData *pHead = AnimationController::GetHeadClip()->frameHead;
	Bone *bResult = pHead->pBone;

	Matrix T = Matrix(TRANS, bResult[indexBoneArray].T);
	Matrix S = Matrix(SCALE, bResult[indexBoneArray].S);
	Quat   Q = bResult[indexBoneArray].Q;

	// Isn't awesome that we can multiply Quat with matrices!
	Matrix M = S * Q * T;
	*this->pLocal = M;

	// Goal: update the world matrix
	*this->pWorld = *this->pLocal * ParentWorld;
}


void GameObjectAnim::Process(Time currentTime)
{
	// Goal: update the world matrix
	this->Update(currentTime);

	// push to graphics object
	Matrix mTmp = *this->pBoneOrientation;

	GraphicsObject *pGraphicsObj = this->GetGraphicsObject();
	assert(pGraphicsObj != 0);
	pGraphicsObj->SetWorld(mTmp);
}