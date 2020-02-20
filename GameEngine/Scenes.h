#ifndef SCENES_H
#define SCENES_H

#include "Engine.h"

#include <sb7.h>
#include <math.h>

//core
#include "MathEngine.h"
#include "Camera.h"

//models
#include "UnitModel.h"

//managers
#include "GameObjectMan.h"
#include "TextureManager.h"
#include "InputMan.h"
#include "CameraManager.h"

//shader
#include "ShaderObject.h"

//util
#include "Colors.h"

//graphics objects
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_Blinn_Phong.h"
#include "GraphicsObject_Toon.h"

void LoadDemoScene();
GameObject *gameObject;
GameObject *rowRootObject;
GameObject *removalDemoObject;
GameObject *textureSwapDemoObject;

GraphicsObject *Wireframe_go;
GraphicsObject *FlatTexture_go;
GraphicsObject *TextureLight_go;
GraphicsObject *BlinnPhong_go;
GraphicsObject *Toon_go;

void LoadDemoScene()
{
	// Load the model
	UnitModel *CubeModel = new UnitModel(Model::ModelType::UnitCube, "cubeModel.whisk");
	assert(CubeModel);

	UnitModel *PyramidModel = new UnitModel(Model::ModelType::UnitPyramid, "pyramidModel.whisk");
	assert(PyramidModel);

	UnitModel *SphereModel = new UnitModel(Model::ModelType::UnitSphere, "sphereModel.whisk");
	assert(SphereModel);

	UnitModel *DiamondModel = new UnitModel(Model::ModelType::Diamond, "diamondModel.whisk");
	assert(SphereModel);

	// Create/Load Shader 

	ShaderObject *colorRender_so = new ShaderObject(ShaderObject::Name::COLOR_LIGHT, "colorRender");
	assert(colorRender_so);

	ShaderObject *texture_so = new ShaderObject(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender");
	assert(texture_so);

	ShaderObject *textureLight_so = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(textureLight_so);

	ShaderObject *blinnPhong_so = new ShaderObject(ShaderObject::Name::BLINN_PHONG, "blinnphong");
	assert(blinnPhong_so);

	ShaderObject *toonShading_so = new ShaderObject(ShaderObject::Name::TOON, "toonshading");
	assert(toonShading_so);

	// Textures must go in the RESOURCES folder in the directory
	TextureManager::Add("metalCrate.tga", TextureManager::Name::METAL_CRATE);
	TextureManager::Add("dogHair.tga", TextureManager::Name::DOG_HAIR, TextureManager::Status::Protected);
	TextureManager::Add("stones.tga", TextureManager::Name::STONES);
	TextureManager::Add("grass.tga", TextureManager::Name::GRASS);
	TextureManager::Add("waves.tga", TextureManager::Name::WAVES);
	TextureManager::Add("earth.tga", TextureManager::Name::EARTH);



	//Create Light
	Vect lightPosition(1.0f, 1.0, 1.0f);

	//Rotation Values for easy demo
	Vect demoRotation(0.0f, 0.05f, 0.0f); //spin
	Vect demoRotation2(0.1f, 0.01f, 0.00f); //spin
											//Vect demoRotation(0.0f, 0.0f, 0.0f); //no spin

											//scale values for easy demo
	Vect demoScale(.5f, .5f, .5f);
	Vect demoScale2(1.0f, 1.0f, 1.0f);

	//Row 1 - Cube Row
	Wireframe_go = new GraphicsObject_Wireframe(CubeModel, colorRender_so);
	rowRootObject = new GameObject(Wireframe_go, Vect(-3.0f, 1.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(rowRootObject);

	FlatTexture_go = new GraphicsObject_FlatTexture(CubeModel, texture_so, TextureManager::Name::METAL_CRATE);
	gameObject = new GameObject(FlatTexture_go, Vect(-1.5f, 1.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	TextureLight_go = new GraphicsObject_TextureLight(CubeModel, textureLight_so, TextureManager::Name::METAL_CRATE, Colors::Red, lightPosition);
	gameObject = new GameObject(TextureLight_go, Vect(-0.0f, 1.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	BlinnPhong_go = new GraphicsObject_Blinn_Phong(CubeModel, blinnPhong_so, lightPosition, Colors::OrangeRed, Colors::Gray);
	gameObject = new GameObject(BlinnPhong_go, Vect(1.5f, 1.5f, 0.0f), demoRotation2, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	Toon_go = new GraphicsObject_Toon(CubeModel, toonShading_so, Colors::White, lightPosition);
	gameObject = new GameObject(Toon_go, Vect(3.0f, 1.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	//Row 2 - Pyramid Row
	Wireframe_go = new GraphicsObject_Wireframe(PyramidModel, colorRender_so);
	rowRootObject = new GameObject(Wireframe_go, Vect(-3.0f, 0.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(rowRootObject);

	FlatTexture_go = new GraphicsObject_FlatTexture(PyramidModel, texture_so, TextureManager::Name::WAVES);
	gameObject = new GameObject(FlatTexture_go, Vect(-1.5f, 0.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	TextureLight_go = new GraphicsObject_TextureLight(PyramidModel, textureLight_so, TextureManager::Name::WAVES, Colors::White, lightPosition);
	gameObject = new GameObject(TextureLight_go, Vect(0.0f, 0.5f, 0.0f), demoRotation2 * 2, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	BlinnPhong_go = new GraphicsObject_Blinn_Phong(PyramidModel, blinnPhong_so, lightPosition, Colors::OrangeRed, Colors::Gray);
	gameObject = new GameObject(BlinnPhong_go, Vect(1.5f, 0.5f, 0.0f), demoRotation, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	Toon_go = new GraphicsObject_Toon(PyramidModel, toonShading_so, Colors::White, lightPosition);
	gameObject = new GameObject(Toon_go, Vect(3.0f, 0.5f, 0.0f), demoRotation2, demoScale);
	GameObjectMan::Add(gameObject, rowRootObject);

	//Row 3 - Sphere Row
	Wireframe_go = new GraphicsObject_Wireframe(SphereModel, colorRender_so);
	rowRootObject = new GameObject(Wireframe_go, Vect(-3.0f, -0.5f, 0.0f), demoRotation2, Vect(.35f, .35f, .35f));
	GameObjectMan::Add(rowRootObject);

	FlatTexture_go = new GraphicsObject_FlatTexture(SphereModel, texture_so, TextureManager::Name::EARTH);
	gameObject = new GameObject(FlatTexture_go, Vect(-1.5f, -0.5f, 0.0f), -demoRotation, Vect(.35f, .35f, .35f));
	GameObjectMan::Add(gameObject, rowRootObject);

	TextureLight_go = new GraphicsObject_TextureLight(SphereModel, textureLight_so, TextureManager::Name::EARTH, Colors::White, lightPosition);
	gameObject = new GameObject(TextureLight_go, Vect(0.0f, -0.5f, 0.0f), demoRotation, Vect(.35f, .35f, .35f));
	GameObjectMan::Add(gameObject, rowRootObject);

	BlinnPhong_go = new GraphicsObject_Blinn_Phong(SphereModel, blinnPhong_so, lightPosition, Colors::OrangeRed, Colors::Gray);
	gameObject = new GameObject(BlinnPhong_go, Vect(1.5f, -0.5f, 0.0f), demoRotation, Vect(.35f, .35f, .35f));
	GameObjectMan::Add(gameObject, rowRootObject);

	Toon_go = new GraphicsObject_Toon(SphereModel, toonShading_so, Colors::White, lightPosition);
	gameObject = new GameObject(Toon_go, Vect(3.0f, -0.5f, 0.0f), demoRotation, Vect(.35f, .35f, .35f));
	GameObjectMan::Add(gameObject, rowRootObject);

	//Row 4 - Diamond Row
	Wireframe_go = new GraphicsObject_Wireframe(DiamondModel, colorRender_so);
	rowRootObject = new GameObject(Wireframe_go, Vect(-3.0f, -1.5f, 0.0f), demoRotation, Vect(.75f, .75f, .75f));
	GameObjectMan::Add(rowRootObject);

	FlatTexture_go = new GraphicsObject_FlatTexture(DiamondModel, texture_so, TextureManager::Name::GRASS);
	removalDemoObject = new GameObject(FlatTexture_go, Vect(-1.5f, -1.5f, 0.0f), demoRotation, demoScale2);
	GameObjectMan::Add(removalDemoObject, rowRootObject);

	TextureLight_go = new GraphicsObject_TextureLight(DiamondModel, textureLight_so, TextureManager::Name::GRASS, Colors::White, lightPosition);
	textureSwapDemoObject = new GameObject(TextureLight_go, Vect(-0.0f, -1.5f, 0.0f), demoRotation2, Vect(.75f, .75f, .75f));
	GameObjectMan::Add(textureSwapDemoObject, rowRootObject);

	BlinnPhong_go = new GraphicsObject_Blinn_Phong(DiamondModel, blinnPhong_so, lightPosition, Colors::OrangeRed, Colors::Gray);
	gameObject = new GameObject(BlinnPhong_go, Vect(1.5f, -1.5f, 0.0f), demoRotation, Vect(.75f, .75f, .75f));
	GameObjectMan::Add(gameObject, rowRootObject);

	Toon_go = new GraphicsObject_Toon(DiamondModel, toonShading_so, Colors::White, lightPosition);
	gameObject = new GameObject(Toon_go, Vect(3.0f, -1.5f, 0.0f), demoRotation, Vect(.75f, .75f, .75f));
	GameObjectMan::Add(gameObject, rowRootObject);

	//Demo to show deletion of texture
	TextureManager::PrintNodeUses();
	Trace::out("~~~~~~~Purging unused Textures~~~~~~~\n");
	TextureManager::PurgeUnusedTextures();
	TextureManager::PrintNodeUses();

}

/*
void Game::LoadContent()
{
	deleted = 0;
	CameraManager::setUpCameras(info.windowWidth, info.windowHeight);

	//Load Shaders
	ShaderObject *textureLight_so = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(textureLight_so);

	ShaderObject *colorRender_so = new ShaderObject(ShaderObject::Name::COLOR_LIGHT, "colorRender");
	assert(colorRender_so);

	UnitModel *SphereModel = new UnitModel(Model::ModelType::UnitSphere, "sphereModel.whisk");


	TextureManager::Add("default_text", TextureManager::Name::DEFAULT, TextureManager::Status::Protected);

	Matrix tempMatrix;

	//Load Models


	//space frigate
	Wireframe_go = new GraphicsObject_Wireframe(SphereModel, colorRender_so, Colors::LightSeaGreen);
	wireSphere = new PhysicsObject(SphereModel, Wireframe_go);

	ImportedModel *space_frigate_mod = new ImportedModel(Model::ModelType::Imported, "space_frigate.rum", 0);
	TextureLight_go = new GraphicsObject_TextureLight(space_frigate_mod, textureLight_so, (TextureManager::Name)0);
	space_frigate = new GameObject(TextureLight_go);
	GameObjectMan::Add(space_frigate);
	PhysicsObjectMan::Add(wireSphere);
	space_frigate->Set(Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(1.0f, 1.0f, 1.0f));
	//space_frigate->SetSpinY(0.05f);

	wireSphere->pSet(space_frigate, space_frigate_mod);


	//astroboy
	Wireframe_go2 = new GraphicsObject_Wireframe(SphereModel, colorRender_so, Colors::LightSeaGreen);
	wireSphere2 = new PhysicsObject(SphereModel, Wireframe_go2);

	ImportedModel *astroBoy_mod = new ImportedModel(Model::ModelType::Imported, "astroboy2.rum", 1);
	TextureLight_go = new GraphicsObject_TextureLight(astroBoy_mod, textureLight_so, (TextureManager::Name)1);
	astroBoy = new GameObject(TextureLight_go);
	GameObjectMan::Add(astroBoy);
	PhysicsObjectMan::Add(wireSphere2);
	astroBoy->Set(Vect(200.0f, 0.0f, 0.0f), Vect(-1.57f, 0.0f, 0.0f), Vect(0.5f, 0.5f, 0.5f));
	astroBoy->SetSpinY(-0.05f);

	wireSphere2->pSet(astroBoy, astroBoy_mod);


	//warBear
	Wireframe_go3 = new GraphicsObject_Wireframe(SphereModel, colorRender_so, Colors::LightSeaGreen);
	wireSphere3 = new PhysicsObject(SphereModel, Wireframe_go3);

	ImportedModel *warBear_mod = new ImportedModel(Model::ModelType::Imported, "warbear.rum", 2);
	TextureLight_go = new GraphicsObject_TextureLight(warBear_mod, textureLight_so, (TextureManager::Name)2); //warbear has textures 2 and 3
	warBear = new GameObject(TextureLight_go);
	GameObjectMan::Add(warBear);
	PhysicsObjectMan::Add(wireSphere3);
	warBear->Set(Vect(-200.0f, -0.0f, 0.0f), Vect(-1.57f, 2.0f, 0.0f), Vect(0.5f, 0.5f, 0.5f));
	warBear->SetSpinY(-0.05f);

	wireSphere3->pSet(warBear, warBear_mod);


	//buggy
	Wireframe_go4 = new GraphicsObject_Wireframe(SphereModel, colorRender_so, Colors::LightSeaGreen);
	wireSphere4 = new PhysicsObject(SphereModel, Wireframe_go4);

	ImportedModel *buggy_mod = new ImportedModel(Model::ModelType::Imported, "buggy.rum", 4);
	TextureLight_go = new GraphicsObject_TextureLight(buggy_mod, textureLight_so, (TextureManager::Name)4);
	buggy = new GameObject(TextureLight_go);
	GameObjectMan::Add(buggy);
	PhysicsObjectMan::Add(wireSphere4);
	buggy->Set(Vect(0.0f, 0.0f, -100.0f), Vect(0.0f, 3.14f / 2, 0.0f), Vect(0.1f, 0.1f, 0.1f));
	buggy->SetSpinY(0.05f);

	wireSphere4->pSet(buggy, buggy_mod);

	//geth trooper
	Wireframe_go5 = new GraphicsObject_Wireframe(SphereModel, colorRender_so, Colors::LightSeaGreen);
	wireSphere5 = new PhysicsObject(SphereModel, Wireframe_go5);

	ImportedModel *geth_mod = new ImportedModel(Model::ModelType::Imported, "Geth_Trooper.rum", 5);
	TextureLight_go = new GraphicsObject_TextureLight(geth_mod, textureLight_so, (TextureManager::Name)5);
	geth = new GameObject(TextureLight_go);
	GameObjectMan::Add(geth);
	PhysicsObjectMan::Add(wireSphere5);
	geth->Set(Vect(-100.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(25.0f, 25.0f, 25.0f));
	geth->SetSpinY(0.05f);

	wireSphere5->pSet(geth, geth_mod);

}

void Game::Update(float currentTime)
{
// Mark our end time.
this->intervalTimer.Toc();

// Update camera - make sure everything is consistent
CameraManager::UpdateCamera();

// update objects
GameObjectMan::Update(this->globalTimer.Toc());
//PhysicsObjectMan::Update(this->globalTimer.Toc());

Keyboard *pKey = InputMan::GetKeyboard();

if (pKey->GetKeyState(AZUL_KEY::KEY_K) && (deleted == 0))
{
//PhysicsObjectMan::DontRender();
deleted = 1;
}
if (pKey->GetKeyState(AZUL_KEY::KEY_O) && (deleted == 1))
{
//PhysicsObjectMan::SetToRender();
deleted = 0;
}
if (pKey->GetKeyState(AZUL_KEY::KEY_P))
{
GraphicsObject_FlatTexture *pGraphicsObj = (GraphicsObject_FlatTexture *)warBear->GetGraphicsObject();
pGraphicsObj->textureName = (TextureManager::Name)3;
}
if (pKey->GetKeyState(AZUL_KEY::KEY_L))
{
GraphicsObject_FlatTexture *pGraphicsObj = (GraphicsObject_FlatTexture *)warBear->GetGraphicsObject();
pGraphicsObj->textureName = (TextureManager::Name)2;
}


static int i = 0;

Trace::out("%d: %f\n", i++, currentTime);

Time elapsedTime = this->intervalTimer.Toc();

int timeInSeconds_ms = Time::Quotient(elapsedTime, Time(Time::ONE_MILLISECOND));

Time timeInMs_remainder = Time::Remainder(elapsedTime, Time(Time::ONE_SECOND));
int timeInSeconds_ms_remainder = Time::Quotient(timeInMs_remainder, Time(Time::ONE_MILLISECOND));

Trace::out(" time in     ms : %d \n", timeInSeconds_ms);
Trace::out(" remainder   ms : %d \n", timeInSeconds_ms_remainder);


// Mark our begin time.
this->intervalTimer.Tic();


}


*/

#endif