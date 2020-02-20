#include <string.h>
#include <sb7.h>


#include "TextureNode.h"

TextureNode::TextureNode()
	: name(TextureManager::Name::NOT_INITIALIZED),
	textureID(0),
	minFilter(GL_LINEAR),
	magFilter(GL_LINEAR),
	horizWrapMode(GL_CLAMP_TO_EDGE),
	vertWrapMode(GL_CLAMP_TO_EDGE),
	numObjectsUsingTexture(0),
	protectionStatus(Status::Unprotected)
{
	memset(this->assetName, 0, TextureManager::ASSET_NAME_SIZE);
}

TextureNode::~TextureNode()
{
	this->prev->next = this->next;
	this->next->prev = this->prev;
	this->prev = 0;
	this->next = 0;
}

void TextureNode::addToUseCounter()
{
	numObjectsUsingTexture++;
}
void TextureNode::removeFromUseCounter()
{
	numObjectsUsingTexture--;
}

void TextureNode::removeAllUses()
{
	numObjectsUsingTexture = 0;
}
int TextureNode::getUseCounter()
{
	return numObjectsUsingTexture;
}
void TextureNode::set(const char * const _assetName,
	TextureManager::Name _name,
	GLuint _TextureID,
	GLenum _minFilter,
	GLenum _magFilter,
	GLenum _horizWrapMode,
	GLenum _vertWrapMode, 
	TextureManager::Status inProtectionStatus)
{
	memset(this->assetName, 0x0, TextureManager::ASSET_NAME_SIZE);
	memcpy(this->assetName, _assetName, TextureManager::ASSET_NAME_SIZE - 1);
	this->name = _name;
	this->magFilter = _magFilter;
	this->minFilter = _minFilter;
	this->horizWrapMode = _horizWrapMode;
	this->vertWrapMode = _vertWrapMode;
	this->textureID = _TextureID;
	this->protectionStatus = (TextureNode::Status)inProtectionStatus;
}
