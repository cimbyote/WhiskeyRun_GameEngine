#ifndef GAME_OBJECT_ANIM_H
#define GAME_OBJECT_ANIM_H

#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "Time.h"

class GameObjectAnim : public GameObject
{
public:
	GameObjectAnim(GraphicsObject  *graphicsObject);

	// Big four
	GameObjectAnim() = delete;
	GameObjectAnim(const GameObjectAnim &) = delete;
	GameObjectAnim & operator = (const GameObjectAnim &) = delete;

	// Added virtual to allow us to have derived objects
	virtual ~GameObjectAnim();

	virtual void Update(Time currentTime) override;
	virtual void Process(Time currentTime) override;

	// Accessors

	// Moved from GameObject	

	void SetIndex(int val);
	void SetBoneOrientation(const Matrix &);
	Matrix GetBoneOrientation(void) const;

public:
	// Moved from GameObject	

	Matrix      *pLocal;
	Matrix		*pBoneOrientation;
	int         indexBoneArray;

	Vect *pScale;
	Vect *pPos;
	Vect *pDof;
	Vect *pUp;


};



#endif