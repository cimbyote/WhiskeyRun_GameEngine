#include <sb7.h>
#include <stdlib.h>
#include <assert.h>

#include "TGA.h"
#include "TextureManager.h"
#include "TextureNode.h"
#include "Trace.h"

TextureManager::TextureManager()
{
	this->active = 0;
}

TextureManager * TextureManager::getManager()
{
	// This is where its actually stored (BSS section)
	static TextureManager textMan;
	return &textMan;
}

void TextureManager::Add(const char * const _assetName, const TextureManager::Name _name, Status inStatus)
{
	GLuint               textureID;
	GLuint *pTextureID = &textureID;

	const char* location = "../Resource/Textures/";

	char absoluteLoc[128];
	strcpy_s(absoluteLoc, sizeof(absoluteLoc), location);
	strcat_s(absoluteLoc, sizeof(absoluteLoc), _assetName);

	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	// Load the texture and get the textureID
	pTextMan->privLoadTexture(absoluteLoc, pTextureID);

	// Create a TextureNode
	TextureNode *pNode = new TextureNode();

	//assert(pNode->name != Name::NOT_INITIALIZED);

	// initialize it
	pNode->set(_assetName, _name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, inStatus);

	// Now add it to the manager
	pTextMan->privAddToFront(pNode, pTextMan->active);
}

void TextureManager::AddFromModel(const char * const _assetName, const TextureManager::Name _name, unsigned char *textureBuff, Status inStatus)
{
	GLuint               textureID;
	GLuint *pTextureID = &textureID;

	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	// Load the texture and get the textureID
	pTextMan->privLoadTexture(textureBuff, pTextureID);

	// Create a TextureNode
	TextureNode *pNode = new TextureNode();

	//assert(pNode->name != Name::NOT_INITIALIZED);

	// initialize it
	pNode->set(_assetName, _name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, inStatus);

	// Now add it to the manager
	pTextMan->privAddToFront(pNode, pTextMan->active);
}

void TextureManager::PurgeUnusedTextures()
{
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		if((pNode->getUseCounter() == 0) &&(pNode->protectionStatus == TextureNode::Status::Unprotected))
		{ 
			TextureNode *temp = (TextureNode *)pNode->next;
			pNode->~TextureNode();
			pNode = temp;
		}
		else
		{
			pNode = (TextureNode *)pNode->next;
		}
	}
}

GLuint TextureManager::Find(const TextureManager::Name _name)
{
	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		if (pNode->name == _name)
		{
			// found it
			break;
		}

		pNode = (TextureNode *)pNode->next;
	}

	return pNode->textureID;
}
void TextureManager::AddUseToTexture(const TextureManager::Name _name)
{
	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		if (pNode->name == _name)
		{
			// found it
			break;
		}

		pNode = (TextureNode *)pNode->next;
	}

	pNode->addToUseCounter();
}

void TextureManager::RemoveUseFromTexture(const TextureManager::Name _name)
{
	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		if (pNode->name == _name)
		{
			// found it
			break;
		}

		pNode = (TextureNode *)pNode->next;
	}

	pNode->removeFromUseCounter();
}

void TextureManager::PrintNodeUses()
{
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		//TextureManager::Name tempName = pNode->name;
		//Trace::out("Texture %d is used %i times\n",tempName, pNode->getUseCounter());
		
		if (pNode->name == TextureManager::Name::METAL_CRATE)
		{
			Trace::out("METAL_CRATE is used %i times.",pNode->getUseCounter());	
		}
		else if(pNode->name == TextureManager::Name::DOG_HAIR)
		{
			Trace::out("DOG_HAIR is used %i times.", pNode->getUseCounter());
		}
		else if(pNode->name == TextureManager::Name::GRASS)
		{
			Trace::out("GRASS is used %i times.", pNode->getUseCounter());
		}
		else if(pNode->name == TextureManager::Name::STONES)
		{
			Trace::out("STONES is used %i times.", pNode->getUseCounter());
		}
		else if(pNode->name == TextureManager::Name::WAVES)
		{
			Trace::out("WAVES is used %i times.", pNode->getUseCounter());
		}
		else if(pNode->name == TextureManager::Name::EARTH)
		{
			Trace::out("EARTH is used %i times.", pNode->getUseCounter());
		}
		else
		{
			Trace::out("fuck\n");
		}
		
		if (pNode->protectionStatus == (TextureNode::Status)Status::Protected)
		{
			Trace::out("Protected\n");
		}
		else if (pNode->protectionStatus == (TextureNode::Status)Status::Unprotected)
		{
			//Trace::out("Unprotected\n");
			Trace::out("\n");
		}

		pNode = (TextureNode *)pNode->next;
	}
}

void TextureManager::DeleteAllTextures()
{
	// Get the instance to the manager
	TextureManager *pTextMan = TextureManager::getManager();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		// bye bye
		glDeleteTextures(1, &pNode->textureID);

		// next
		pNode = (TextureNode *)pNode->next;
	}
}

void TextureManager::privAddToFront(TextureNodeLink *node, TextureNodeLink *&head)
{
	assert(node != 0);

	if (head == 0)
	{
		head = node;
		node->next = 0;
		node->prev = 0;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

void TextureManager::privLoadTexture(const char * const _assetName, GLuint *&textureID)
{
	// Get an ID, for textures (OpenGL poor man's handle)
	glGenTextures(1, textureID);

	// Bind it.
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Loat the texture
	this->privLoadTGATexture(_assetName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void TextureManager::privLoadTexture(unsigned char *textureBuff, GLuint *&textureID)
{
	// Get an ID, for textures (OpenGL poor man's handle)
	glGenTextures(1, textureID);

	// Bind it.
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Loat the texture
	this->privLoadTGATexture(textureBuff, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

// Load a TGA as a 2D Texture. Completely initialize the state
bool TextureManager::privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	/*
	const char* location = "../Resource/Texture/";

	char absoluteLoc[128];
	strcpy_s(absoluteLoc, sizeof(absoluteLoc), location);
	strcat_s(absoluteLoc, sizeof(absoluteLoc), szFileName);
	*/
	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
	{
		return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, horizWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vertWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return true;
}

bool TextureManager::privLoadTGATexture(unsigned char *textureBuff, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	// Read the texture bits
	pBits = gltReadTGABits(textureBuff, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
	{
		return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, horizWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vertWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return true;
}


////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *TextureManager::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	fopen_s(&pFile, szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width *  (unsigned int)tgaHeader.height *  (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{

	case 3:     // Most likely case
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;

	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		// bad case - keenan
		// i commented out
		//  *eFormat = GL_LUMINANCE;
		//  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
					// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!

		break;
	}



	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}
GLbyte *TextureManager::gltReadTGABits(unsigned char *textureBuff, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	//FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits
									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	//fopen_s(&pFile, szFileName, "rb");
	//if (pFile == NULL)
	//	return NULL;

	// Read in header (binary)
	//fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	/*
	TGAHEADER

	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
	
	*/
	
	unsigned char* tempBuff = new unsigned char[18];
	memcpy(tempBuff, textureBuff, 18);

	memcpy((void*)&tgaHeader, textureBuff, 18);

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width *  (unsigned int)tgaHeader.height *  (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize

	//if (fread(pBits, lImageSize, 1, pFile) != 1)
	//{
	//	free(pBits);
	//	return NULL;
	//}

	memcpy_s((void*)pBits, lImageSize, textureBuff + 18, lImageSize);

	// Set OpenGL format expected
	switch (sDepth)
	{

	case 3:     // Most likely case
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;

	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		// bad case - keenan
		// i commented out
		//  *eFormat = GL_LUMINANCE;
		//  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
					// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!

		break;
	}



	// Done with File
	//fclose(pFile);

	// Return pointer to image data
	return pBits;
}