#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "ImportedModel.h"
#include "Time.h"

class GameObject : public PCSNode
{
public:
	GameObject(GraphicsObject  *graphicsObject);
	GameObject(GraphicsObject  *graphicsObject, Vect inPosition, Vect inRotation, Vect inScale);

	// Big four
	GameObject() = delete;
	GameObject(const GameObject &) = delete;
	GameObject &operator=(GameObject &) = delete;
	virtual ~GameObject();

	virtual void Update(Time currentTime);
	virtual void Process(Time currentTime);
	void Draw();

	GraphicsObject *GetGraphicsObject();
	Matrix *GetWorld();

	void SetWorld(Matrix *pWorld);
	void Set(const Vect &inPos, const Vect &inRot, const Vect &inScale);
	void Set(GameObject *inObject, ImportedModel *mod);

	void SetPos(const Vect &pos);
	void SetScale(const Vect &scale);

	void SetRotX(float in);
	void SetRotY(float in);
	void SetRotZ(float in);
	void SetRot(float x, float y, float z);
	void SetRot(const Vect &inScale);

	void SetSpinX(float in);
	void SetSpinY(float in);
	void SetSpinZ(float in);
	void SetSpin(float x, float y, float z);
	void SetSpin(const Vect &inScale);

	Vect* GetPosition();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	Vect GetSpin();
	Vect GetRotation();

	float deltaSpinX;
	float deltaSpinY;
	float deltaSpinZ;

public:
	Vect *pScale;
	Vect *pPos;
	Vect *pDof;
	Vect *pUp;


protected:
	Matrix *pWorld;
private:
	GraphicsObject  *pGraphicsObject;
	Vect *pTrans;
	float rotX;
	float rotY;
	float rotZ;

};

#endif