#ifndef EAT_H
#define EAT_H

#include "ChunkHeader.h"
#include "ModelFileHeader.h"

bool eat(const char * const inFileName,
	ChunkType type,
	ModelFileHeader &modelHeader,
	unsigned int &thingsInside,
	unsigned char *&chunkBuff,
	unsigned int &chunkSize,
	int index = 1);

bool eatModelFileHeader(
	const char * const inFileName,
	ModelFileHeader &modelHeader);
#endif