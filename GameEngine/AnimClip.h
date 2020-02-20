#ifndef ANIMCLIP_H
#define ANIMCLIP_H

#include "FrameData.h"
#include "SkeletonHeader.h"

class AnimClip
{
public:

	enum ClipName
	{
		TeddyWalk,
		TeddyIdle,
		HumanoidWalk,
		HumanoidPunch
	};

	AnimClip();
	void loadAnimFromFile(ClipName clipName, const char * const pModelFileName);

	void SetFrameBucketHead(FrameData *pHead);
	FrameData* GetFrameBucketHead();


	unsigned int numberOfFrames;
	FrameData *frameHead;

	AnimClip *nextClip;
	AnimClip *prevClip;

	ClipName clipName;

};

#endif