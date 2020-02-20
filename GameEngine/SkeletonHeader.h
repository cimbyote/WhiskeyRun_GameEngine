#ifndef SKELETON_HEADER_H
#define SKELETON_HEADER_H

struct SkeletonHeader
{
	/*
	Need:
	Name
	Index
	Parent Name (Index?)
	*/

	char	Name[32];
	char	parentName[32];
	int		index;
};

#endif