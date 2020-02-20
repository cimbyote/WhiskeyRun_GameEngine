#ifndef MODEL_FILE_HEADER_H
#define MODEL_FILE_HEADER_H

#include <string.h>

#define OBJECT_NAME_SIZE   32
#define TEXTURE_NAME_SIZE  32


struct ModelFileHeader
{
	//names
	char			packageName[20];				//  52
	char			versionString[20];				//	72

	unsigned int	numChunks;					//4		//76
	unsigned int	totalSize;					//4		//80

	int				numMeshes;					//4		//84
	int				numTextures;				//4		//88

	unsigned int	totalNumVerts;				//4		//92
	unsigned int	totalNumTriList;			//4		//96


												//unsigned int textMinFilter;
												//unsigned int textMagFilter;
												//unsigned int textWrapMode;

	ModelFileHeader()
	{
		memset(this, 0x0, sizeof(ModelFileHeader));
	}
};


#endif