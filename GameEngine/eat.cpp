//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Optimized C++
//----------------------------------------------------------------------------- 

#include <stdio.h>
#include <assert.h>

#include "eat.h"
#include "ChunkHeader.h"

#include "File.h"

#define UNUSED_VAR(x) ((void *)x)

bool eat(const char * const inFileName, ChunkType type,
			ModelFileHeader &packageHeader,unsigned int &thingsInside, 
			unsigned char *&chunkBuff, unsigned int &chunkSize, int index)
{
	File::Handle fh;

	const char* location = "../Resource/Models/";

	char absoluteLoc[128];
	strcpy_s(absoluteLoc, sizeof(absoluteLoc), location);
	strcat_s(absoluteLoc, sizeof(absoluteLoc), inFileName);

	char stringBuff[16];
	unsigned int numBuff[1];

	if (File::Open(fh, absoluteLoc, File::Mode::READ) == File::Error::SUCCESS)
	{

		ChunkHeader chunkHead;
		//Two counters to ensure it's progressing as expected
		int forwardCounter = sizeof(ModelFileHeader);
		int backCounter = sizeof(ModelFileHeader);

		bool correctChunkFlag = false;
		int chunkCounter = 0;
		while ((correctChunkFlag == false) && (chunkCounter < (int)packageHeader.numChunks)) {

			//type
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, numBuff, sizeof(ChunkType));
			chunkHead.type = (ChunkType)numBuff[0];
			forwardCounter += sizeof(ChunkType);

			//name but don't copy to chunkhead yet
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, stringBuff, 16);
			//don't bother copying yet.
			forwardCounter += 16;

			//size
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, numBuff, sizeof(unsigned int));
			chunkHead.chunkSize = numBuff[0];
			forwardCounter += sizeof(unsigned int);

			//hashNum
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, numBuff, sizeof(unsigned int));
			chunkHead.hashNum = numBuff[0];
			forwardCounter += sizeof(unsigned int);

			//things inside
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, numBuff, sizeof(unsigned int));
			chunkHead.thingsInside = numBuff[0];
			forwardCounter += sizeof(unsigned int);


			//Index
			File::Seek(fh, File::Location::BEGIN, forwardCounter);
			File::Read(fh, numBuff, sizeof(unsigned int));
			chunkHead.index = (int)numBuff[0];
			forwardCounter += sizeof(unsigned int);

			//ok, now you have the header...
			//check if it's the right one...
			//if ((chunkHead.type == type) && (strcmp(chunkName, stringBuff) == 0))
			if ((chunkHead.type == type) &&(chunkHead.index == index))
			{
				thingsInside = chunkHead.thingsInside;
				correctChunkFlag = true;
			}
			else
			{
				backCounter += sizeof(ChunkHeader) + chunkHead.chunkSize;
				forwardCounter = backCounter;
				chunkCounter++;
			}
		}

		if (correctChunkFlag == true)
		{
			chunkSize = chunkHead.chunkSize;
			strcpy_s(chunkHead.chunkName, 16, stringBuff);
			chunkBuff = new unsigned char[chunkSize];

			File::Seek(fh, File::Location::BEGIN, (int)forwardCounter);
			File::Read(fh, chunkBuff, chunkSize);

			File::Close(fh);
			return true;
		}
		else
		{
			File::Close(fh);
			return false;
		}
	}
	else
	{
		File::Close(fh);
		return false;
	}

}

bool eatModelFileHeader(const char * const inFileName, ModelFileHeader &modelHeader)
{
	const char* location = "../Resource/Models/";

	char absoluteLoc[128];
	strcpy_s(absoluteLoc, sizeof(absoluteLoc), location);
	strcat_s(absoluteLoc, sizeof(absoluteLoc), inFileName);

	File::Handle fh;

	char stringBuff[sizeof(ModelFileHeader)];
	unsigned int numBuff[sizeof(ModelFileHeader)];
	if (File::Open(fh, absoluteLoc, File::Mode::READ) == File::Error::SUCCESS)
	{
		//get the PackageHeader, so we can get the rest of the information
		//Package Name
		File::Seek(fh, File::Location::BEGIN, 0);
		File::Read(fh, stringBuff, sizeof(ModelFileHeader));
		strcpy_s(modelHeader.packageName, 20, stringBuff);

		//version string
		File::Seek(fh, File::Location::BEGIN, 20);
		File::Read(fh, stringBuff, 20);
		strcpy_s(modelHeader.versionString, 20, stringBuff);

		File::Seek(fh, File::Location::BEGIN, 40);
		File::Read(fh, numBuff, sizeof(ModelFileHeader)-40);
		
		modelHeader.numChunks = numBuff[0];
		modelHeader.totalSize = numBuff[1];
		modelHeader.numMeshes = (int)numBuff[2];
		modelHeader.numTextures = (int)numBuff[3];
		modelHeader.totalNumVerts = numBuff[4];
		modelHeader.totalNumTriList = numBuff[5];

		File::Close(fh);
		return true;
	}
	else
	{
		File::Close(fh);
		return false;
	}

}