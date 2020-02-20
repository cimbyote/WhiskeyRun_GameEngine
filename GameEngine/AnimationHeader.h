#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

struct AnimationHeader
{
	int frameNum;
	int boneNum;

	float Tx;
	float Ty;
	float Tz;

	float Qx;
	float Qy;
	float Qz;

	float Sx;
	float Sy;
	float Sz;
};
#endif