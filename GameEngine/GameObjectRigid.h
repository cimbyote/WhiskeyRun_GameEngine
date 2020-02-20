#ifndef GAME_OBJECT_RIGID_H
#define GAME_OBJECT_RIGID_H

#include "GameObject.h"
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObjectRigid : public GameObject
{
public:
	GameObjectRigid(GraphicsObject  *graphicsObject);

	// Big Four
	GameObjectRigid() = delete;
	GameObjectRigid(GameObjectRigid &) = delete;
	GameObjectRigid & operator = (const GameObjectRigid &) = delete;
	virtual ~GameObjectRigid() override;

	virtual void SetPos(Vect inVect);
	virtual void Update(Time currentTime) override;

	Matrix &GetWorld();

public:
	Vect *pScale;
	Vect *pPos;

};

#endif