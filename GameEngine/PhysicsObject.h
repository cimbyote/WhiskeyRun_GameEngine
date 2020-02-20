#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "UnitModel.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "ImportedModel.h"
#include "GameObjectMan.h"

class PhysicsObject : public PCSNode
{
public:
	PhysicsObject(UnitModel* boundingSphere, GraphicsObject  *graphicsObject);
	PhysicsObject(GraphicsObject  *graphicsObject);
	//big four
	PhysicsObject() = delete;
	PhysicsObject(const PhysicsObject &) = delete;
	PhysicsObject &operator=(PhysicsObject &) = delete;
	virtual ~PhysicsObject();

	void pSet(GameObject *inObject, ImportedModel *mod);


	void Update(Time t);
	void Draw();
	void Process(Time t);


	GraphicsObject *pGetGraphicsObject();
	Matrix *pGetWorld();

	void pSetWorld(Matrix *pWorld);
	void pSet(const Vect &inPos, const Vect &inRot, const Vect &inScale);
	void pSetPos(const Vect &pos);
	void pSetScale(const Vect &scale);

	void pSetRotX(float in);
	void pSetRotY(float in);
	void pSetRotZ(float in);
	void pSetRot(float x, float y, float z);
	void pSetRot(const Vect &inScale);

	void pSetSpinX(float in);
	void pSetSpinY(float in);
	void pSetSpinZ(float in);
	void pSetSpin(float x, float y, float z);
	void pSetSpin(const Vect &inScale);

	Vect* pGetPosition();
	float pgetScaleX();
	float pgetScaleY();
	float pgetScaleZ();
	Vect pGetSpin();
	Vect pGetRotation();

	//Vect center;
	float radius;
	float deltaSpinX;
	float deltaSpinY;
	float deltaSpinZ;

	UnitModel* pBoundingSphere;
	GameObject* gameObject;

	
	

protected:
	Matrix *pWorld;
public:
	bool render;
private:
	char padding;
	char padding2;
	char padding3;
	GraphicsObject  *pGraphicsObject;
	Vect *pTrans;
	Vect *pScale;
	float rotX;
	float rotY;
	float rotZ;

};

#endif