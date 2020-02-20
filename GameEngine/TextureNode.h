#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "TextureManager.h"
#include "TextureNodeLink.h"

class TextureNode : public TextureNodeLink
{

public:
	TextureNode();
	~TextureNode();
	enum class Status
	{
		Unprotected,
		Protected
	};
	

	void set(const char * const _assetName,
		TextureManager::Name _name,
		GLuint _TextureID,
		GLenum minFilter,
		GLenum magFilter,
		GLenum horizWrapMode,
		GLenum vertWrapMode,
		TextureManager::Status inProtectionStatus);

	void addToUseCounter();
	void removeFromUseCounter();
	void removeAllUses();
	int getUseCounter();

private:
	char assetName[TextureManager::ASSET_NAME_SIZE];

public:
	TextureManager::Name name;
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum horizWrapMode;
	GLenum vertWrapMode;

	int numObjectsUsingTexture;
	Status protectionStatus;
};

#endif