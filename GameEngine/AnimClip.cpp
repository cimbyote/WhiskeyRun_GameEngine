#include "AnimClip.h"

#include "AnimationController.h"
#include "eat.h"
#include "AnimationHeader.h"
#include "Trace.h"

AnimClip::AnimClip()
{
	this->nextClip = 0;
	this->prevClip = 0;

	numberOfFrames = 0;
}




void AnimClip::SetFrameBucketHead(FrameData *inpHead)
{
	frameHead = inpHead;
}

FrameData* AnimClip::GetFrameBucketHead()
{
	return frameHead;
}

void AnimClip::loadAnimFromFile(ClipName inName, const char * const pModelFileName)
{
	clipName = inName;

	unsigned char *chunkBuff;
	unsigned int chunkSize;

	ModelFileHeader modelHdr;
	modelHdr.numChunks = 0;

	eatModelFileHeader(pModelFileName, modelHdr);

	unsigned int framesInside;

	bool flag = eat(pModelFileName, ChunkType::ANIM_TYPE, modelHdr, framesInside, chunkBuff, chunkSize);

	unsigned int numBones = modelHdr.totalNumVerts;

	assert(flag == true);

	AnimationHeader *tempHeader = new AnimationHeader;
	tempHeader->boneNum = 0;
	tempHeader->frameNum = 0;
	tempHeader->Tx = 0.0f;
	tempHeader->Ty = 0.0f;
	tempHeader->Tz = 0.0f;
	tempHeader->Qx = 0.0f;
	tempHeader->Qy = 0.0f;
	tempHeader->Qz = 0.0f;
	tempHeader->Sx = 0.0f;
	tempHeader->Sy = 0.0f;
	tempHeader->Sz = 0.0f;

	// --------  Result Frame  ----------------------
	frameHead = new FrameData();

	SetFrameBucketHead(frameHead);

	frameHead->prevBucket = 0;
	frameHead->nextBucket = 0;
	frameHead->KeyTime = Time(Time::ZERO);
	frameHead->pBone = new Bone[numBones];

	FrameData *tempFrame;

	tempFrame = frameHead;

	//for each frame
	for (unsigned int frameNum = 0; frameNum < framesInside; frameNum++) {

		//memcpy((void*)tempHeader, (void*)(chunkBuff + (j * sizeof(AnimationHeader))), sizeof(AnimationHeader));

		FrameData *pTmp0 = new FrameData();
		pTmp0->prevBucket = tempFrame;
		pTmp0->nextBucket = 0;
		pTmp0->KeyTime = (int)frameNum * Time(Time::NTSC_30_FRAME);
		pTmp0->pBone = new Bone[numBones];

		pTmp0->pBone->T = Vect(0.0f, 0.0f, 0.0f);
		pTmp0->pBone->S = Vect(1.0f, 1.0f, 1.0f);
		pTmp0->pBone->Q = Quat(0.0f, 0.0f, 0.0f, 0.0f);

		tempFrame->nextBucket = pTmp0;

		tempFrame = pTmp0;

		unsigned int offset = 0;

		for (unsigned int i = 0; i < numBones; i++)
		{
			offset = ((frameNum * (numBones * sizeof(AnimationHeader))) + (i * sizeof(AnimationHeader)));

			memcpy((void*)tempHeader, (void*)(chunkBuff + offset), sizeof(AnimationHeader));

			pTmp0->pBone[i].T = Vect(tempHeader->Tx, tempHeader->Ty, tempHeader->Tz);
			pTmp0->pBone[i].Q = Quat(ROT_XYZ, tempHeader->Qx, tempHeader->Qy, tempHeader->Qz);
			pTmp0->pBone[i].S = Vect(tempHeader->Sx, tempHeader->Sy, tempHeader->Sz);

			//Trace::out("Frame %i - Bone:%i T: %f, %f, %f\n", frameNum, i, tempHeader->Tx, tempHeader->Ty, tempHeader->Tz);
			//Trace::out("Frame %i - Bone:%i Q: %f, %f, %f\n", frameNum, i, tempHeader->Qx, tempHeader->Qy, tempHeader->Qz);
			//Trace::out("Frame %i - Bone:%i S: %f, %f, %f\n", frameNum, i, tempHeader->Sx, tempHeader->Sy, tempHeader->Sz);

		}
	}

	delete[] chunkBuff;
}
