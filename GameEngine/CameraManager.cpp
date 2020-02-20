#include <assert.h>
#include "InputMan.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Trace.h"
#include "CameraNode.h"
#include "PhysicsObjectMan.h"
#include "PCSTreeForwardIterator.h"

CameraManager *CameraManager::pCameraManager = 0;

//Camera *activeCam = 0;

void CameraManager::Create()
{
	CameraManager::privCreate();
}

void CameraManager::setUpCameras(int inWidth, int inHeight)
{

	CameraManager *camManager = CameraManager::getManager();

	camManager->activeCamera = 0;
	camManager->currCamera = 0;

	Camera *camera0 = new Camera();
	camera0->setViewport(0, 0, inWidth, inHeight);
	camera0->setPerspective(35.0f, float(inWidth) / float(inHeight), 1.0f, 10000.0f);

	camManager->startCamPosition = new CamValues();
	camManager->startCamPosition->positionVect.set(Vect(0.0f, 0.0f, 200.0f));
	camManager->startCamPosition->camTarget.set(Vect(0.0f, 100.0f, 10.0f));
	camManager->startCamPosition->up.set(Vect(0.0f, 1.0f, 0.0f));

	SetCamValues(*camera0, *getManager()->startCamPosition); //set the default values, and set cam 0 to those values

	camera0->updateCamera();

	Add(Camera::Name::CAMERA_0, camera0);
	SetCurrent(Camera::Name::CAMERA_0);

	Camera *camera1 = new Camera();
	camera1 = new Camera();
	camera1->setViewport(0, 0, inWidth, inHeight);
	camera1->setPerspective(35.0f, float(inWidth) / float(inHeight), 1.0f, 10000.0f);
	camera1->setUp_Target_Pos(Vect(0.0f, 0.0f, 1.0f), Vect(-389.433502f, -1325.91895f, -1289.87817f), Vect(-461.584015f, -1501.01599f, -1274.42456f));
	camera1->updateCamera();
	
	Add(Camera::Name::CAMERA_1, camera1);
	//SetCurrent(Camera::Name::CAMERA_1);

	Camera *camera2 = new Camera();
	camera2 = new Camera();
	camera2->setViewport(0, 0, inWidth, inHeight);
	camera2->setPerspective(50.0f, float(inWidth) / float(inHeight), 0.10f, 1000.0f);
	camera2->setUp_Target_Pos(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 10.0f));
	camera2->updateCamera();

	Add(Camera::Name::CAMERA_2, camera2);
	//SetCurrent(Camera::Name::CAMERA_2);

	//set up the struct to hold the values for the default camera position.
	


}
void CameraManager::UpdateCamera()
{
	CameraManager *camManager = CameraManager::getManager();

	Camera *inCamera = camManager->GetCurrent();

	inCamera->updateCamera();

	Keyboard *pKey = InputMan::GetKeyboard();

	if (pKey->GetKeyState(AZUL_KEY::KEY_W))
	{
		inCamera->moveCameraForward();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_S))
	{
		inCamera->moveCameraBack();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_A))
	{
		inCamera->rotateLeftAroundTarget();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_D))
	{
		inCamera->rotateRightAroundTarget();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		inCamera->spinCamRight();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		inCamera->spinCamLeft();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		inCamera->panCameraUp();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		inCamera->panCameraDown();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_E))
	{
		inCamera->panCameraLeft();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_Q))
	{
		inCamera->panCameraRight();
	}

	//Reset Camera Position
	if (pKey->GetKeyState(AZUL_KEY::KEY_0))
	{
		SetCamValues(*inCamera, *getManager()->startCamPosition);
		Trace::out("Camera Reset\n");
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_1))
	{
		CameraManager::SetCurrent(Camera::Name::CAMERA_0);
		Trace::out("Camera1 Active\n");
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_2))
	{
		CameraManager::SetCurrent(Camera::Name::CAMERA_1);
		Trace::out("Camera2 Active\n");
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_3))
	{
		CameraManager::SetCurrent(Camera::Name::CAMERA_2);
		Trace::out("Camera3 Active\n");
	}


	//camManager->Cull();
}

void CameraManager::UpdateDefaultCamera()
{
	CameraManager *camManager = CameraManager::getManager();

	Camera *inCamera = camManager->Find(Camera::Name::CAMERA_0);

	inCamera->updateCamera();

	Keyboard *pKey = InputMan::GetKeyboard();

	if (pKey->GetKeyState(AZUL_KEY::KEY_W))
	{
		inCamera->moveCameraForward();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_S))
	{
		inCamera->moveCameraBack();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_A))
	{
		inCamera->rotateLeftAroundTarget();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_D))
	{
		inCamera->rotateRightAroundTarget();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		inCamera->spinCamRight();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		inCamera->spinCamLeft();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		inCamera->panCameraUp();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		inCamera->panCameraDown();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_E))
	{
		inCamera->panCameraLeft();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_Q))
	{
		inCamera->panCameraRight();
	}

	inCamera->updateCamera();

	if (pKey->GetKeyState(AZUL_KEY::KEY_0))
	{
		SetCamValues(*inCamera, *getManager()->startCamPosition);
		Trace::out("Camera Reset\n");
	}

	if (pKey->GetKeyState(AZUL_KEY::KEY_1))
	{
		CameraManager::SetCurrent(Camera::Name::CAMERA_0);
		Trace::out("Camera1 Active\n");
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_2))
	{
		CameraManager::SetCurrent(Camera::Name::CAMERA_1);
		Trace::out("Camera2 Active\n");
	}


	//camManager->Cull();
}
void CameraManager::Cull()
{
	CameraManager *camManager = CameraManager::getManager();

	//if object is outside of this, change color, else, nothing
	//get the data
	Camera *tempCam = camManager->Find(Camera::Name::CAMERA_0);


	//get the object & pass in data to object 

	PCSNode *rootNode = PhysicsObjectMan::GetRootNode();

	PCSTreeForwardIterator pForwardIter(rootNode);
	PCSNode *pNode = pForwardIter.First();

	PhysicsObject *pGameObj = 0;

	Vect *positionTemp;

	float distanceForward = 0.0f;
	float distanceBackward = 0.0f;
	float distanceLeft = 0.0f;
	float distanceRight = 0.0f;
	float distanceUp = 0.0f;
	float distanceDown = 0.0f;

	Camera::CameraNorms camNorms;
	tempCam->getCameraNorms(camNorms);

	Camera::CameraFrustrum camFrustrum;
	tempCam->getCameraFrustrumInfo(camFrustrum);

	while (!pForwardIter.IsDone())
	{

		assert(pNode);
		// Update the game object
		pGameObj = (PhysicsObject *)pNode;
		//pGameObj->render = true;
		positionTemp = pGameObj->pGetPosition();

		//do calcs
		/*
		n dot (p2-p1) / magnitude of n(?)
		*/

	
		distanceForward = camNorms.forward.dot(*positionTemp - camFrustrum.farTopRight);
		distanceBackward = camNorms.backward.dot(*positionTemp - camFrustrum.nearTopRight);
		distanceLeft = camNorms.left.dot(*positionTemp - camFrustrum.nearTopLeft);
		distanceRight = camNorms.right.dot(*positionTemp - camFrustrum.nearTopRight);
		distanceUp = camNorms.up.dot(*positionTemp - camFrustrum.nearTopLeft);
		distanceDown = camNorms.down.dot(*positionTemp - camFrustrum.nearBottomRight);

	
		if ((distanceUp <= -pGameObj->radius) && (distanceDown <= -pGameObj->radius) && (distanceForward >= -pGameObj->radius) && (distanceBackward >= -pGameObj->radius) && (distanceLeft <= -pGameObj->radius) && (distanceRight <= -pGameObj->radius))
		{
			pGameObj->render = true;
		}
		else
		{
			pGameObj->render = false;
		}

		pNode = pForwardIter.Next();
	}
	

	//repeat for all 6 sides

	//repeat for all objects
}

void CameraManager::Add(Camera::Name name, Camera *pCamera)
{
	CameraManager *pCameraMan = CameraManager::getManager();

	CameraNode *pNode = new CameraNode();

	pCamera->setName(name);
	pNode->set(pCamera);

	pCameraMan->AddToFront(pNode, pCameraMan->activeCamera);
}

void CameraManager::AddToFront(CameraLink *node, CameraLink *&head)
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

Camera * CameraManager::Find(Camera::Name _name)
{
	// Get the instance to the manager
	CameraManager *pCameraMan = CameraManager::getManager();
	assert(pCameraMan);

	CameraNode *pNode = (CameraNode *)pCameraMan->activeCamera;
	while (pNode != 0)
	{
		if (pNode->pCamera->getName() == _name)
		{
			// found it
			break;
		}

		pNode = (CameraNode *)pNode->next;
	}
	assert(pNode);
	return pNode->pCamera;
}

void CameraManager::SetCurrent(const Camera::Name name)
{
	CameraManager *pCameraMan = CameraManager::getManager();

	Camera *pCam = CameraManager::Find(name);

	pCameraMan->currCamera = pCam;
}

Camera *  CameraManager::GetCurrent()
{
	CameraManager *pCameraMan = CameraManager::getManager();

	return pCameraMan->currCamera;
}


//wrapper thing to keep Camera decoupled from the Manager
void CameraManager::SetCamValues(Camera &inCamera, CamValues inValues)
{
	inCamera.setUp_Target_Pos(inValues.up, inValues.camTarget, inValues.positionVect);
}

CameraManager::CameraManager()
{

}

void CameraManager::privCreate()
{
	CameraManager::pCameraManager = new CameraManager();
	assert(pCameraManager);
}

CameraManager::~CameraManager()
{
	
}

CameraManager *CameraManager::getManager()
{
	assert(pCameraManager);
	return pCameraManager;
}
