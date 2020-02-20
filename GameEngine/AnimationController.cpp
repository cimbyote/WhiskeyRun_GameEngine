#include <assert.h>

#include "AnimationController.h"
#include "PCSTreeForwardIterator.h"
#include "Trace.h"


AnimationController::AnimationController()
{
	skeleton = new Skeleton();
	headClip = 0;
	currentClip = headClip;
}

void AnimationController::AddClip(AnimClip *inClip, AnimClip::ClipName name)
{
	inClip->clipName = name;

	AnimationController *controller = AnimationController::getManager();

	if (controller->headClip != nullptr) {
		controller->headClip->prevClip = inClip;
		inClip->nextClip = controller->headClip;
		controller->headClip = inClip;
		controller->currentClip = inClip;
	}
	else {
		controller->headClip = inClip;
		controller->currentClip = inClip;
		controller->currentClip = inClip;
	}
}



GameObjectRigid*  AnimationController::SetAnimationSkeleton(Skeleton::SkelName anim, const char * const pModelFileName)
{
	AnimationController *controller = AnimationController::getManager();

	GameObjectRigid * temp = controller->skeleton->loadBonesFromFile(anim, pModelFileName);

	controller->numBones = controller->skeleton->GetNumBones();

	return temp;
}

void AnimationController::AddAnimationClip(Skeleton::SkelName anim, AnimClip::ClipName name, const char * const pModelFileName)
{
	AnimClip *clip = new AnimClip();
	AnimationController::AddClip(clip, name);

	shutUp(anim);

	clip->loadAnimFromFile(name, pModelFileName);

}

void AnimationController::SwapClips()
{
	AnimationController *controller = AnimationController::getManager();


	if (controller->currentClip->nextClip != nullptr)
	{
		controller->currentClip = controller->currentClip->nextClip;

	}
	else
	{
		controller->currentClip = controller->headClip;
	}
}


void AnimationController::SetCurrentClip(AnimClip::ClipName clip)
{
	AnimationController *controller = AnimationController::getManager();

	controller->currentClip = controller->GetClipByName(clip);
}

AnimClip *AnimationController::GetClipByName(AnimClip::ClipName name)
{
	AnimationController *controller = AnimationController::getManager();

	AnimClip *tempClip = controller->GetHeadClip();

	while (tempClip != nullptr)
	{
		if (tempClip->clipName == name)
		{
			return tempClip;
		}

		tempClip = tempClip->nextClip;
	}

	return nullptr;
}


Skeleton* AnimationController::GetSkeleton()
{
	AnimationController *controller = AnimationController::getManager();

	return controller->skeleton;
}
AnimClip*  AnimationController::GetCurrentClip()
{
	AnimationController *controller = AnimationController::getManager();

	return controller->currentClip;
}

AnimClip*  AnimationController::GetHeadClip()
{
	AnimationController *controller = AnimationController::getManager();

	return controller->headClip;
}

void AnimationController::FindMaxTime(Time &tMax)
{
	AnimationController *controller = AnimationController::getManager();
	FrameData *pTmp = controller->currentClip->frameHead->nextBucket;

	//FrameData *pTmp = controller->headClip->frameHead->nextBucket;

	while (pTmp->nextBucket != 0)
	{
		pTmp = pTmp->nextBucket;
	}

	tMax = pTmp->KeyTime;
}


void AnimationController::UpdateSkeleton(GameObject *inNode, Time tCurr)
{
	//Frame_Bucket *pTmp = pHead->nextBucket;
	AnimationController *controller = AnimationController::getManager();

	controller->skeleton->SetAnimationPose(inNode, tCurr);
}

void AnimationController::ProcessAnimation(Time tCurr)
{
		//Frame_Bucket *pTmp = pHead->nextBucket;
		AnimationController *controller = AnimationController::getManager();

		FrameData *pTmp = controller->currentClip->frameHead->nextBucket;
		// Get the result bone array
		// Remember the first Frame is the result
		Bone *bResult = controller->headClip->frameHead->pBone;

		// First one is the result, skip it
		pTmp = controller->currentClip->frameHead->nextBucket;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime  && pTmp->nextBucket != 0)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameData *pA = pTmp->prevBucket;
		FrameData *pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		// interpolate to 
		Bone *bA = pA->pBone;
		Bone *bB = pB->pBone;

		// Interpolate to tS time, for all bones
		for (int i = 0; i < controller->numBones; i++)
		{
			// interpolate ahoy!
			VectApp::Lerp(bResult->T, bA->T, bB->T, tS);
			QuatApp::Slerp(bResult->Q, bA->Q, bB->Q, tS);
			VectApp::Lerp(bResult->S, bA->S, bB->S, tS);

			// advance the pointer
			bA++;
			bB++;
			bResult++;
		
	}
}

AnimationController * AnimationController::getManager(void)
{
	// This is where its actually stored (BSS section)
	static AnimationController manager;
	return &manager;
}