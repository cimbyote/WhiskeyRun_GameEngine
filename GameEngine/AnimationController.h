#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include "Skeleton.h"
#include "FrameData.h"
#include "AnimClip.h"
#include "GameObjectRigid.h"


//#define NUM_BONES 20

// Singleton
class AnimationController
{
public:

	static Skeleton* GetSkeleton();

	static GameObjectRigid* SetAnimationSkeleton(Skeleton::SkelName anim, const char * const pModelFileName);
	static void AddAnimationClip(Skeleton::SkelName anim, AnimClip::ClipName name, const char * const pModelFileName);

	static void SwapClips();
	static void SetCurrentClip(AnimClip::ClipName clip);
	static AnimClip * GetCurrentClip();
	static AnimClip * GetClipByName(AnimClip::ClipName name);


	static AnimClip * GetHeadClip();
	static void AddClip(AnimClip *inClip, AnimClip::ClipName name);

	static void ProcessAnimation(Time tCurr);
	static void UpdateSkeleton(GameObject *inNode, Time tCurr);
	static void FindMaxTime(Time &tMax);

private:
	AnimationController();
	static AnimationController *getManager();
	//PCSTree *pRootTree;


	int numBones;

	Skeleton *skeleton;

	AnimClip *headClip;
	AnimClip *currentClip;
};

#endif