#pragma once
#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"


// Singleton
class GameObjectMan
{
public:

	static void Add(GameObject *inObject);
	static void Add(GameObject *inObject, GameObject *parentObject);
	static void Remove(GameObject *inObject);
	static void Draw(void);
	static void Update(Time currentTime);
	static GameObject *GetRoot(void);
	static PCSNode* GetRootNode();
	static PCSTree *GetTree();

private:
	GameObjectMan();
	static GameObjectMan *getManager();
	PCSTree *pRootTree;

};

#endif