#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "sb7.h"

#include "TextureNodeLink.h"

class TextureManager
{
public:
	static const unsigned int ASSET_NAME_SIZE = 64;

	enum class Name
	{
		TEXT_1,
		TEXT_2,
		TEXT_3,
		TEXT_4,
		TEXT_5,
		DEFAULT,
		METAL_CRATE,
		DOG_HAIR,
		GRASS,
		STONES,
		WAVES,
		EARTH,
		NOT_INITIALIZED
	};
	enum class Status
	{
		Unprotected,
		Protected
	};

public:
	TextureManager(const TextureManager &) = delete;
	TextureManager & operator = (const TextureManager &) = delete;
	~TextureManager() = default;

	static void Add(const char * const _assetName, const TextureManager::Name _name, const Status inStatus = Status::Unprotected);
	static void AddFromModel(const char * const _assetName,  const TextureManager::Name _name, unsigned char *textureBuff, const Status inStatus = Status::Unprotected);
	static void PurgeUnusedTextures();
	static void DeleteAllTextures();
	static GLuint Find(const TextureManager::Name _name);
	static void AddUseToTexture(const TextureManager::Name _name);
	static void RemoveUseFromTexture(const TextureManager::Name _name);

	static void PrintNodeUses();
private:
	// methods
	TextureManager();
	static TextureManager *getManager();

	// helper private methods
	void privLoadTexture(const char * const _assetName, GLuint *&textureID);
	bool privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode);

	void privAddToFront(TextureNodeLink *node, TextureNodeLink *&head);
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);


	void privLoadTexture(unsigned char *textureBuff, GLuint *&textureID);
	bool privLoadTGATexture(unsigned char *textureBuff, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode);
	GLbyte *gltReadTGABits(unsigned char *textureBuff, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
private:

	TextureNodeLink *active;
};

#endif