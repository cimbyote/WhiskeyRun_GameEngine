#include <assert.h>

#include "NullModel.h"
#include "GraphicsObject_Null.h"

#include "GameObject.h"
#include "PhysicsObjectMan.h"
#include "PCSTreeForwardIterator.h"

void PhysicsObjectMan::Add(PhysicsObject *inObject)
{
	assert(inObject != 0);

	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();

	gameManager->pRootTree->Insert(inObject, pRootNode);
}
void PhysicsObjectMan::Add(PhysicsObject *inObject, GameObject *parentObject)
{
	assert(inObject != 0);

	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	gameManager->pRootTree->Insert(inObject, parentObject);
}

void PhysicsObjectMan::Remove(PhysicsObject *inObject)
{
	assert(inObject != 0);

	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();


	//PCSNode *pRootNode = gameManager->pRootTree->GetRoot();

	gameManager->pRootTree->Remove(inObject);
}

void PhysicsObjectMan::Update(Time currentTime)
{
	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	PhysicsObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (PhysicsObject *)pNode;
		pGameObj->Process(currentTime);

		pNode = pForwardIter.Next();
	}
}
void PhysicsObjectMan::DontRender()
{
	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	PhysicsObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (PhysicsObject *)pNode;
		pGameObj->render = false;

		pNode = pForwardIter.Next();
	}
}
void PhysicsObjectMan::SetToRender()
{
	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	PhysicsObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (PhysicsObject *)pNode;
		pGameObj->render = true;

		pNode = pForwardIter.Next();
	}
}
PCSNode* PhysicsObjectMan::GetRootNode()
{
	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();

	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	return pRootNode;
}

void PhysicsObjectMan::Draw()
{
	PhysicsObjectMan *gameManager = PhysicsObjectMan::getManager();
	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	PhysicsObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (PhysicsObject *)pNode;
		pGameObj->Draw();

		pNode = pForwardIter.Next();
	}
}

PhysicsObjectMan::PhysicsObjectMan()
{
	// Create the root node (null object)
	NullModel *pModel = new NullModel(0);
	ShaderObject *pShader = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender");
	GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pModel, pShader);
	PhysicsObject *pGameRoot = new PhysicsObject(pGraphicsObject);
	pGameRoot->SetName("PhysicsObject_Root");

	// Create the tree
	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	// Attach the root node
	this->pRootTree->Insert(pGameRoot, this->pRootTree->GetRoot());
}

PhysicsObjectMan * PhysicsObjectMan::getManager(void)
{
	// This is where its actually stored (BSS section)
	static PhysicsObjectMan manager;
	return &manager;
}
