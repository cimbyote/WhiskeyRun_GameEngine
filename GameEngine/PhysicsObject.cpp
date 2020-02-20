#include <math.h>
#include <assert.h>

#include "Game.h"
#include "MathEngine.h"
#include "PhysicsObject.h"

extern Game *pGame;


Matrix *PhysicsObject::pGetWorld()
{
	return this->pWorld;
}


PhysicsObject::PhysicsObject(UnitModel* boundingSphere, GraphicsObject  *graphicsObject)
	: pGraphicsObject(graphicsObject)
{
	this->pBoundingSphere = boundingSphere;

	this->pWorld = new Matrix(IDENTITY);
	this->pTrans = new Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(pGraphicsObject != 0);

	this->rotX = 0.0f;
	this->rotY = 0.0f;
	this->rotZ = 0.0f;
	this->deltaSpinX = 0.0f;
	this->deltaSpinY = 0.0f;
	this->deltaSpinZ = 0.0f;

	render = true;
}

PhysicsObject::PhysicsObject(GraphicsObject  *graphicsObject)
	: pGraphicsObject(graphicsObject)
{
	this->pBoundingSphere = nullptr;

	this->pWorld = new Matrix(IDENTITY);
	this->pTrans = new Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(pGraphicsObject != 0);

	this->rotX = 0.0f;
	this->rotY = 0.0f;
	this->rotZ = 0.0f;
	this->deltaSpinX = 0.0f;
	this->deltaSpinY = 0.0f;
	this->deltaSpinZ = 0.0f;

	render = true;
}


PhysicsObject::~PhysicsObject()
{
	delete this->pWorld;
}
void PhysicsObject::pSet(GameObject *inObject, ImportedModel *mod)
{
	this->radius = mod->radius * inObject->getScaleX();
	//this->center = Vect(mod->centerX, mod->centerY, mod->centerZ);

	this->deltaSpinX = inObject->deltaSpinX;
	this->deltaSpinY = inObject->deltaSpinY;
	this->deltaSpinZ = inObject->deltaSpinZ;

	this->gameObject = inObject;

	float trueDiameter = mod->radius * 2 * inObject->getScaleX();
	
	Matrix m2;
	m2.set(MatrixTransType::TRANS, Vect(0.0f, mod->centerY, mod->centerZ));
	
	this->pSetWorld(&m2);
	
	m2 = *this->pGetWorld() * *inObject->GetWorld();
	this->pSetWorld(&m2);
	this->pSetPos(this->pGetWorld()->get(MatrixRowType::ROW_3));
	
	this->pSetRot(inObject->GetRotation());
	this->pSetScale(Vect(trueDiameter, trueDiameter, trueDiameter));
	
	//this->Update(0);
}
void PhysicsObject::pSet(const Vect &inPos, const Vect &inRot, const Vect &inScale)
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




void PhysicsObject::Update(Time currentTime)
{
	shutUp(currentTime);

	// Goal: update the world matrix

	this->rotX += deltaSpinX;
	this->rotY += deltaSpinY;
	this->rotZ += deltaSpinZ;

	Matrix Scale(SCALE, *this->pScale);
	Matrix TransA(TRANS, *this->pTrans);
	Matrix RotX(ROT_X, this->rotX);
	Matrix RotY(ROT_Y, this->rotY);
	Matrix RotZ(ROT_Z, this->rotZ);

	RotX *= RotY;
	RotX *= RotZ;

	*this->pWorld = Scale * RotX * TransA;

}

void PhysicsObject::Draw()
{
	assert(this->pGraphicsObject);
	if (render == true) {
		this->pGraphicsObject->Render();
	}
}

void PhysicsObject::Process(Time currentTime)
{
	// Goal: update the world matrix
	this->Update(currentTime);

	// push to graphics object
	this->pGraphicsObject->SetWorld(*this->pWorld);
}


void PhysicsObject::pSetWorld(Matrix *_pWorld)
{
	assert(_pWorld);
	*this->pWorld = *_pWorld;
}

void PhysicsObject::pSetPos(const Vect &pos)
{
	*this->pTrans = pos;
}

void PhysicsObject::pSetScale(const Vect &inScale)
{
	*this->pScale = inScale;
}
void PhysicsObject::pSetRotX(float in)
{
	this->rotX = in;
}
void PhysicsObject::pSetRotY(float in)
{
	this->rotY = in;
}
void PhysicsObject::pSetRotZ(float in)
{
	this->rotZ = in;
}
void PhysicsObject::pSetRot(float x, float y, float z)
{
	this->rotX = x;
	this->rotY = y;
	this->rotZ = z;
}
void PhysicsObject::pSetRot(const Vect &inNum)
{
	this->rotX = inNum.x();
	this->rotY = inNum.y();
	this->rotZ = inNum.z();
}

void PhysicsObject::pSetSpinX(float in)
{
	this->deltaSpinX = in;
}
void PhysicsObject::pSetSpinY(float in)
{
	this->deltaSpinY = in;
}
void PhysicsObject::pSetSpinZ(float in)
{
	this->deltaSpinZ = in;
}
void PhysicsObject::pSetSpin(float x, float y, float z)
{
	this->deltaSpinX = x;
	this->deltaSpinY = y;
	this->deltaSpinZ = z;
}
void PhysicsObject::pSetSpin(const Vect &inScale)
{
	this->deltaSpinX = inScale.x();
	this->deltaSpinY = inScale.y();
	this->deltaSpinZ = inScale.z();
}

GraphicsObject *PhysicsObject::pGetGraphicsObject()
{
	return this->pGraphicsObject;
}

Vect PhysicsObject::pGetSpin()
{
	return Vect(this->deltaSpinX, this->deltaSpinY, this->deltaSpinZ);
}

Vect* PhysicsObject::pGetPosition()
{
	return this->pTrans;
}

float PhysicsObject::pgetScaleX() { return this->pScale->x(); }
float PhysicsObject::pgetScaleY() { return this->pScale->y(); }
float PhysicsObject::pgetScaleZ() { return this->pScale->z(); }

Vect PhysicsObject::pGetRotation()
{
	return Vect(this->rotX, this->rotY, this->rotZ);
}


