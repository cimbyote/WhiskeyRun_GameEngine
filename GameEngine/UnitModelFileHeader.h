#ifndef UNIT_MODEL_FILE_HEADER_H
#define UNIT_MODEL_FILE_HEADER_H

#include <string.h>

#define OBJECT_NAME_SIZE   32
#define TEXTURE_NAME_SIZE  32


struct UnitModelFileHeader
{
	//names
	char			objName[20];			
	char			textName[20];						

	int				numMeshes;				
	int				numTextures;			

	int	numVerts;				
	unsigned int	vertBufferOffset;		
	int	numTriList;
	unsigned int	triListBufferOffset;


	UnitModelFileHeader()
	{
		memset(this, 0x0, sizeof(UnitModelFileHeader));
	}
};


#endif