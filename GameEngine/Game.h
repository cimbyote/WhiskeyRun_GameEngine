#ifndef GAME_H
#define GAME_H


//core
#include "Engine.h"
#include <sb7.h>
#include "MathEngine.h"
#include "Camera.h"

//util
#include "Time.h"
#include "Timer.h"

//models
#include "UnitModel.h"
#include "ImportedModel.h"
#include "PyramidModel.h"

//managers
#include "GameObjectMan.h"
#include "PhysicsObjectMan.h"
#include "TextureManager.h"
#include "InputMan.h"
#include "CameraManager.h"

//shader
#include "ShaderObject.h"

//graphics objects
#include "GraphicsObjects.h"

//Animation
#include "AnimationController.h"


class Game : public Engine
{
public:

	//big 4
	Game() = delete;
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	~Game() = default;

	Game(const char* windowName, const int Width, const int Height);

	void Initialize();
	virtual void LoadContent();
	virtual void Update(float currentTime);
	virtual void Draw();
	virtual void UnLoadContent();
	virtual void ClearBufferFunc();

public:
	// Create GameObject
	//GameObject *space_frigate;
	//GameObject *astroBoy;
	//GameObject *buggy;
	//GameObject *warBear;
	//GameObject *geth;

	//PhysicsObject *wireSphere;
	//PhysicsObject *wireSphere2;
	//PhysicsObject *wireSphere3;
	//PhysicsObject *wireSphere4;
	//PhysicsObject *wireSphere5;
	//
	//// GraphicsObject 
	//GraphicsObject *Wireframe_go;
	//GraphicsObject *Wireframe_go2;
	//GraphicsObject *Wireframe_go3;
	//GraphicsObject *Wireframe_go4;
	//GraphicsObject *Wireframe_go5;
	//
	//GraphicsObject *FlatTexture_go;
	//
	//GraphicsObject *BlinnPhong_go;
	//GraphicsObject *Toon_go;

	//dumb flag to show deletion (prevents double deletion)
	
	Time deltaTime;
	
	Timer	intervalTimer;
	Timer	globalTimer;
	float animSpeed;
	int deleted;
	int padding;
	int padding2;
};

#endif
