#include <assert.h>

#include "NullModel.h"
#include "GraphicsObject_Null.h"

#include "GameObject.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"
#include "Trace.h"


void GameObjectMan::Add(GameObject *inObject)
{
	assert(inObject != 0);

	GameObjectMan *gameManager = GameObjectMan::getManager();

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();

	gameManager->pRootTree->Insert(inObject, pRootNode);
}
void GameObjectMan::Add(GameObject *inObject, GameObject *parentObject)
{
	assert(inObject != 0);

	GameObjectMan *gameManager = GameObjectMan::getManager();


	gameManager->pRootTree->Insert(inObject, parentObject);
}

void GameObjectMan::Remove(GameObject *inObject)
{
	assert(inObject != 0);

	GameObjectMan *gameManager = GameObjectMan::getManager();

	//PCSNode *pRootNode = gameManager->pRootTree->GetRoot();

	gameManager->pRootTree->Remove(inObject);
}

void GameObjectMan::Update(Time currentTime)
{
	GameObjectMan *gameManager = GameObjectMan::getManager();
	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode->GetChild());

	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	//char * const tempBuff = new char[32];
	//unsigned int tempInt = 32;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		pGameObj->Process(currentTime);

		//pGameObj->GetName(tempBuff, tempInt);

		//Trace::out(tempBuff);
		//Trace::out("\n       x: %f\n", pGameObj->GetWorld()->m12());
		//Trace::out("	   y: %f\n", pGameObj->GetWorld()->m13());
		//Trace::out("	   z: %f\n\n", pGameObj->GetWorld()->m14());

		pNode = pForwardIter.Next();
	}
}
PCSTree *GameObjectMan::GetTree()
{
	// Get singleton
	GameObjectMan *gameManager = GameObjectMan::getManager();
	assert(gameManager);

	// Get root node
	return gameManager->pRootTree;
}

GameObject * GameObjectMan::GetRoot()
{
	// Get singleton
	GameObjectMan *gameManager = GameObjectMan::getManager();
	assert(gameManager);

	GameObject *pGameObj = (GameObject *)gameManager->pRootTree->GetRoot();
	assert(pGameObj);

	return pGameObj;
}

PCSNode* GameObjectMan::GetRootNode()
{
	GameObjectMan *gameManager = GameObjectMan::getManager();
	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	return pRootNode;
}

void GameObjectMan::Draw()
{
	GameObjectMan *gameManager = GameObjectMan::getManager();
	assert(gameManager);

	PCSNode *pRootNode = gameManager->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		pGameObj->Draw();

		pNode = pForwardIter.Next();
	}
}

GameObjectMan::GameObjectMan()
{
	// Create the root node (null object)
	NullModel *pModel = new NullModel(0);
	ShaderObject *pShader = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender");
	GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pModel, pShader);
	GameObject *pGameRoot = new GameObject(pGraphicsObject);
	pGameRoot->SetName("GameObject_Root");

	// Create the tree
	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	// Attach the root node
	this->pRootTree->Insert(pGameRoot, this->pRootTree->GetRoot());
}

GameObjectMan * GameObjectMan::getManager(void)
{
	// This is where its actually stored (BSS section)
	static GameObjectMan manager;
	return &manager;
}
