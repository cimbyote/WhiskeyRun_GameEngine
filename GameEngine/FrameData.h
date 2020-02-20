#ifndef FRAME_DATA
#define FRAME_DATA

#include "Timer.h"
#include "Vect.h"
#include "Quat.h"

struct Bone : public Align16
{
	Vect  T;
	Quat  Q;
	Vect  S;
};

struct FrameData
{
	FrameData *nextBucket;
	FrameData *prevBucket;
	Time		  KeyTime;
	Bone		  *pBone;
	char		  pad[4];
};


#endif