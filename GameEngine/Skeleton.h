#ifndef SKELETON_H
#define SKELETON_H

#include "Timer.h"
#include "Vect.h"
#include "Quat.h"
#include "GameObject.h"
#include "GameObjectAnim.h"
#include "ChunkHeader.h"
#include "GameObjectRigid.h"

//#define NUM_BONES 40

class Skeleton : PCSNode
{
public:
	enum SkelName
	{
		TeddyBear,
		Worm,
		Humanoid,
		MISSINGNO
	};
	GameObjectRigid* loadBonesFromFile(SkelName anim, const char * const pModelFileName);

	void setBonePose(GameObject *node);
	
	void SetAnimationPose(GameObject *root, Time tCurr);

	GameObjectAnim *findObjectWithIndex(int inNum);
	
	GameObjectAnim *findObjectWithName(char *inName);

	int GetNumBones();

private:
	int numBones;
};
#endif