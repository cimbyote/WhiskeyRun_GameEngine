#include <assert.h>

#include "PyramidModel.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_Null.h"
#include "GameObjectMan.h"
#include "eat.h"
#include "Skeleton.h"
#include "Colors.h"
#include "PCSTreeForwardIterator.h"
#include "AnimationController.h"
#include "SkeletonHeader.h"
#include "Trace.h"
#include "NullModel.h"

//#define BONE_WIDTH 8.0f //<---- best for Bear
#define BONE_WIDTH 18.0f //<---- best for Humanoid

GameObject *pFirstBone;

PCSNode *root = 0;

int Skeleton::GetNumBones()
{
	return this->numBones;
}

GameObjectRigid* Skeleton::loadBonesFromFile(SkelName anim, const char * const pModelFileName)
{
	shutUp(anim);

	GraphicsObject_TextureLight *TextureLight_go;
	GraphicsObject_Null *Null_go;

	PyramidModel* pPyramidModel = new PyramidModel("pyramidModel.azul");
	assert(pPyramidModel);

	// Create/Load Shader 
	ShaderObject* textureLight_so = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(textureLight_so);

	unsigned char *chunkBuff;
	unsigned int chunkSize;

	ModelFileHeader modelHdr;
	modelHdr.numChunks = 0;


	eatModelFileHeader(pModelFileName, modelHdr);

	unsigned int thingsInside;

	bool flag = eat(pModelFileName, ChunkType::ANIM_TYPE, modelHdr, thingsInside, chunkBuff, chunkSize);
	assert(flag == true);

	numBones = (int)modelHdr.totalNumVerts;

	SkeletonHeader *tempHeader = new SkeletonHeader;


	// Null object
	NullModel *pNullModel = new NullModel(0);
	GraphicsObject_Null *pGameObjNull = new GraphicsObject_Null(pNullModel, textureLight_so);
	GameObjectRigid *pGameRigid = new GameObjectRigid(pGameObjNull);
	pGameRigid->SetName("Rigid");
	GameObjectMan::Add(pGameRigid);

	pGameRigid->SetPos(Vect(100.0f, 0.0f, 0.0f));

	memcpy((void*)tempHeader, chunkBuff, 64);
	tempHeader->index = atoi((const char*)chunkBuff + 64);

	Null_go = new GraphicsObject_Null(pPyramidModel, textureLight_so);
	GameObjectAnim *first = new GameObjectAnim(Null_go);
	first->SetIndex(tempHeader->index);
	first->SetName(tempHeader->Name);
	GameObjectMan::Add(first, pGameRigid);

	pFirstBone = first;

	memcpy((void*)tempHeader, chunkBuff + (sizeof(SkeletonHeader) * 1), 64);
	tempHeader->index = atoi((const char*)chunkBuff + 64 + (sizeof(SkeletonHeader) * 1));

	Null_go = new GraphicsObject_Null(pPyramidModel, textureLight_so);
	GameObjectAnim *second = new GameObjectAnim(Null_go);
	second->SetIndex(tempHeader->index);
	second->SetName(tempHeader->Name);
	GameObjectMan::Add(second, first);

	//PCSTree *boneTree = GameObjectMan::GetTree();
	//boneTree->Print();
	//PCSTree::Info info;

	//note totalNumVerts actually just holds the number of bones here
	for (int i = 2; i < numBones; i++) {
		memcpy((void*)tempHeader, chunkBuff + (sizeof(SkeletonHeader) * i), 64);
		tempHeader->index = atoi((const char*)chunkBuff + 64 + (sizeof(SkeletonHeader) * i));

		TextureLight_go = new GraphicsObject_TextureLight(pPyramidModel, textureLight_so);
		GameObjectAnim *tempObj = new GameObjectAnim(TextureLight_go);
		tempObj->SetIndex(tempHeader->index);
		tempObj->SetName(tempHeader->Name);

		GameObjectAnim *parentObj = findObjectWithName(tempHeader->parentName);
		GameObjectMan::Add(tempObj, parentObj);
		
		//boneTree = GameObjectMan::GetTree();
		//Trace::out("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		
		//boneTree->Print();
		//boneTree->GetInfo(info);
		//Trace::out("Number of Nodes: %i\n", info.currNumNodes);
	}
	
	//boneTree = GameObjectMan::GetTree();
	//boneTree->Print();
	//boneTree->GetInfo(info);
	//Trace::out("Number of Nodes: %i\n", info.currNumNodes);
	delete[] chunkBuff;

	return pGameRigid;
}

GameObjectAnim * Skeleton::findObjectWithName(char *inName)
{
	PCSTree *boneTree = GameObjectMan::GetTree();
	root = boneTree->GetRoot();

	PCSTreeForwardIterator pIter(root);
	GameObjectAnim *temp = (GameObjectAnim*)pIter.First();

	char * const tempBuff = new char[32];
	unsigned int tempInt = 32;
	while (temp != 0)
	{
		temp->GetName(tempBuff, tempInt);

		if(strcmp(tempBuff, inName) != 0)
		{
			temp = (GameObjectAnim*)pIter.Next();
		}
		else
		{
			return temp;
		}
	}
	delete[] tempBuff;
	return temp;
}

GameObjectAnim * Skeleton::findObjectWithIndex(int inNum)
{
	PCSTree *boneTree = GameObjectMan::GetTree();
	root = boneTree->GetRoot();

	PCSTreeForwardIterator pIter(root);
	GameObjectAnim *temp = (GameObjectAnim*)pIter.First();

	while ((temp != 0)&&(temp->indexBoneArray != inNum))
	{
		
		temp = (GameObjectAnim*)pIter.Next();
	}

	return temp;
}

void Skeleton::SetAnimationPose(GameObject *inNode, Time tCurr)
{
	PCSTreeForwardIterator pIter(inNode);
	PCSNode *pNode = pIter.First();
	GameObject *pGameObj = 0;

	// walks the anim node does the pose for everything that
	while (pNode != 0)
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		setBonePose(pGameObj);

		pNode = pIter.Next();
	}
}

void Skeleton::setBonePose(GameObject *node)
{
	// Now get the world matrices
	// getting the parent from current node
	GameObjectAnim *childNode = (GameObjectAnim *)node;
	GameObjectAnim *parentNode = (GameObjectAnim *)node->GetParent();

	if (parentNode == root) {
		return;
	}

	if (parentNode != 0 && childNode != 0)
	{
		// starting point
		Vect start(0.0f, 0.0f, 0.0f);

		//  At this point, Find the two bones initial positions in world space
		//  Now get the length and directions

		Vect ptA = start * *parentNode->GetWorld();
		Vect ptB = start * *childNode->GetWorld();

		// direction between the anchor points of the respective bones
		Vect dir = (ptA - ptB);

		// length of the bone 0
		float mag = dir.mag();

		Matrix S(SCALE, BONE_WIDTH, BONE_WIDTH, mag);

		Vect up(0.0f, 1.0f, 0.0f);
		up = up * *parentNode->GetWorld();

		Quat Q(ROT_ORIENT, dir.getNorm(), up);
		Matrix T(TRANS, ptB);

		Matrix BoneOrient = S * Q * T;
		childNode->SetBoneOrientation(BoneOrient);
	}

}