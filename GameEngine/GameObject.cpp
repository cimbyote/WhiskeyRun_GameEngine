#include <math.h>
#include <assert.h>

#include "Game.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "FrameData.h"

extern FrameData *pHead;

Matrix *GameObject::GetWorld()
{
	return this->pWorld;
}

GameObject::GameObject(GraphicsObject  *pGraphicsObject)
	: pGraphicsObject(pGraphicsObject)
{
	assert(pGraphicsObject != 0);

	this->pWorld = new Matrix(IDENTITY);
	assert(pWorld);

	
}

GameObject::GameObject(GraphicsObject  *pGraphicsObject, Vect inPosition, Vect inRotation, Vect inScale)
	: pGraphicsObject(pGraphicsObject)
{
	this->pWorld = new Matrix(IDENTITY);
	this->pTrans = new Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	*this->pTrans = inPosition;
	*this->pScale = inScale;
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(pGraphicsObject != 0);

	this->rotX = inRotation.x();
	this->rotY = inRotation.y();
	this->rotZ = inRotation.z();
	this->deltaSpinX = 0.0f;
	this->deltaSpinY = 0.0f;
	this->deltaSpinZ = 0.0f;
}

GraphicsObject *GameObject::GetGraphicsObject()
{
	return this->pGraphicsObject;
}

GameObject::~GameObject()
{
	delete this->pWorld;
}

void GameObject::Update(Time currentTime)
{
	shutUp(currentTime);
	
	// Get the parent world
	Matrix M(IDENTITY);

	*this->pWorld = M;
	
}

void GameObject::Process(Time currentTime)
{
	// Goal: update the world matrix
	this->Update(currentTime);

	this->pGraphicsObject->SetWorld(*this->pWorld);
}

void GameObject::Set(const Vect &inPos, const Vect &inRot, const Vect &inScale)
{
	*this->pTrans = inPos;
	*this->pScale = inScale;
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(pGraphicsObject != 0);

	this->rotX = inRot.x();
	this->rotY = inRot.y();
	this->rotZ = inRot.z();
	this->deltaSpinX = 0.0f;
	this->deltaSpinY = 0.0f;
	this->deltaSpinZ = 0.0f;

	//this->Update(0);
}

void GameObject::SetWorld(Matrix *_pWorld)
{
	assert(_pWorld);
	*this->pWorld = *_pWorld;
}
void GameObject::SetPos(const Vect &pos)
{
	*this->pTrans = pos;
}

void GameObject::SetScale(const Vect &inScale)
{
	*this->pScale = inScale;
}

void GameObject::SetRotX(float in)
{
	this->rotX = in;
}
void GameObject::SetRotY(float in)
{
	this->rotY = in;
}
void GameObject::SetRotZ(float in)
{
	this->rotZ = in;
}
void GameObject::SetRot(float x, float y, float z)
{
	this->rotX = x;
	this->rotY = y;
	this->rotZ = z;
}
void GameObject::SetRot(const Vect &inNum)
{
	this->rotX = inNum.x();
	this->rotY = inNum.y();
	this->rotZ = inNum.z();
}

void GameObject::SetSpinX(float in)
{
	this->deltaSpinX = in;
}
void GameObject::SetSpinY(float in)
{
	this->deltaSpinY = in;
}
void GameObject::SetSpinZ(float in)
{
	this->deltaSpinZ = in;
}
void GameObject::SetSpin(float x, float y, float z)
{
	this->deltaSpinX = x;
	this->deltaSpinY = y;
	this->deltaSpinZ = z;
}
void GameObject::SetSpin(const Vect &inScale)
{
	this->deltaSpinX = inScale.x();
	this->deltaSpinY = inScale.y();
	this->deltaSpinZ = inScale.z();
}

Vect GameObject::GetSpin()
{
	return Vect(this->deltaSpinX,this->deltaSpinY,this->deltaSpinZ);
}

Vect* GameObject::GetPosition()
{
	return this->pTrans;
}

float GameObject::getScaleX() {return this->pScale->x();}
float GameObject::getScaleY() {return this->pScale->y();}
float GameObject::getScaleZ() {return this->pScale->z();}

Vect GameObject::GetRotation()
{
	return Vect(this->rotX, this->rotY, this->rotZ);
}


void GameObject::Set(GameObject *inObject, ImportedModel *mod)
{
	float trueDiameter = mod->radius * 2 * inObject->getScaleX();


	Matrix m2;
	m2.set(MatrixTransType::TRANS, Vect(0.0f, mod->centerY, mod->centerZ));

	this->SetWorld(&m2);

	m2 = *this->GetWorld() * *inObject->GetWorld();
	this->SetWorld(&m2);
	this->SetPos(this->GetWorld()->get(MatrixRowType::ROW_3));

	this->SetRot(inObject->GetRotation());
	this->SetScale(Vect(trueDiameter, trueDiameter, trueDiameter));

	//this->Update(0);
}

void GameObject::Draw()
{
	assert(this->pGraphicsObject);
	this->pGraphicsObject->Render();
}