#pragma once
#ifndef PHYSICS_OBJECT_MAN_H
#define PHYSICS_OBJECT_MAN_H

#include "PhysicsObject.h"
#include "PCSTree.h"


// Singleton
class PhysicsObjectMan
{
public:

	static void Add(PhysicsObject *inObject);
	static void Add(PhysicsObject *inObject, GameObject *parentObject);
	static void Remove(PhysicsObject *inObject);
	static void Draw(void);
	static void Update(Time currentTime);

	static void DontRender();
	static void SetToRender();

	static PCSNode* GetRootNode();

private:
	PhysicsObjectMan();
	static PhysicsObjectMan *getManager();
	PCSTree *pRootTree;

};

#endif