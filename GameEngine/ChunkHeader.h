#ifndef CHUNK_HEADER_H
#define CHUNK_HEADER_H

enum ChunkType
{
	MODEL_INFO_TYPE = 0xA0000000,
	VERTS_TYPE,
	TRI_TYPE,
	NORMS_TYPE,
	ANIM_TYPE,
	TEXTURE_TYPE,
	UV_TYPE
};

struct ChunkHeader
{

	// data:
	ChunkType      type;			//4
	char           chunkName[16];	//20
	unsigned int   chunkSize;		//24
	unsigned int   hashNum;			//28
	unsigned int   thingsInside;	//32
	int            index;			//36
};

#endif