#include <assert.h>
#include <math.h>

#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "FrameData.h"
#include "GameObjectRigid.h"

GameObjectRigid::GameObjectRigid(GraphicsObject  *graphicsObject)
	: GameObject(graphicsObject)
{
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(this->pScale);

	this->pPos = new Vect(0.0f, 0.0f, 0.0f);
	assert(this->pPos);
}

GameObjectRigid::~GameObjectRigid()
{
}

void GameObjectRigid::SetPos(Vect inVect)
{
	*this->pPos = inVect;
}


Matrix &GameObjectRigid::GetWorld()
{
	return *this->pWorld;
}

void GameObjectRigid::Update(Time)
{
	Matrix T = Matrix(TRANS, *this->pPos);
	Matrix S = Matrix(SCALE, *this->pScale);

	static float angle = 0.0f;
	angle += 0.0f;
	Matrix R = Matrix(ROT_Z, angle);

	Matrix M = S * R * T;

	*this->pWorld = M;
}