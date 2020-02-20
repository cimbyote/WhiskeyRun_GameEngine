//http://patorjk.com/software/taag/#p=display&c=c&f=Doom&t=Set%20and%20Gets Comment Formatter thing

#include <sb7.h>
#include <math.h>

#include "Game.h"
#include "Scenes.h"
#include "CameraModel.h"

#include "Time.h"
#include "Timer.h"

#include "VectApp.h"
#include "QuatApp.h"
#include "GameObjectRigid.h"

extern GameObject *pFirstBone;
int controlTimer = 0;


Game::Game(const char* pWindowName, const int Width, const int Height)
	:Engine(pWindowName, Width, Height)
{
	assert(pWindowName);
	this->globalTimer.Tic();
	this->intervalTimer.Tic();
}

void Game::Initialize()
{
	InputMan::Create();
	CameraManager::Create();

	animSpeed = 0.2f;
}


void Game::LoadContent()
{
	CameraManager::setUpCameras(info.windowWidth, info.windowHeight);	

	//Load Shaders
	TextureManager::Add("default_text.tga", TextureManager::Name::DEFAULT, TextureManager::Status::Protected);

	GameObjectRigid *rigid = AnimationController::SetAnimationSkeleton(Skeleton::SkelName::TeddyBear, "teddy.bns");
	AnimationController::AddAnimationClip(Skeleton::SkelName::TeddyBear, AnimClip::ClipName::TeddyIdle, "teddy_idle.anm");
	AnimationController::AddAnimationClip(Skeleton::SkelName::TeddyBear, AnimClip::ClipName::TeddyWalk, "teddy_walk.anm");
	rigid->SetPos(Vect(0.0f, 75.0f, -100.0f));


	//GameObjectRigid *rigid = AnimationController::SetAnimationSkeleton(Skeleton::SkelName::Humanoid, "humanoid.bns");
	//AnimationController::AddAnimationClip(Skeleton::SkelName::Humanoid, AnimClip::ClipName::HumanoidPunch, "humanoid.anm");
	//AnimationController::AddAnimationClip(Skeleton::SkelName::Humanoid, AnimClip::ClipName::HumanoidWalk, "humanoid_walk.anm");
	//rigid->SetPos(Vect(150.0f, 500.0f, -2000.0f));

}

void Game::Update(float currentTime)
{
	shutUp(currentTime);
	static Time tCurrent(Time::ZERO);
	static Time zeroTime(Time::ZERO);

	Keyboard *pKey = InputMan::GetKeyboard();

	if (pKey->GetKeyState(AZUL_KEY::KEY_COMMA))
	{
		animSpeed -= 0.01f;
		Trace::out("animationSpeed: %f\n", animSpeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_PERIOD))
	{
		animSpeed += 0.01f;
		Trace::out("animationSpeed: %f\n", animSpeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		animSpeed = 0.0f;
		Trace::out("animationSpeed: %f\n", animSpeed);
	}

	if ((pKey->GetKeyState(AZUL_KEY::KEY_P)) &&(controlTimer > 30))
	{
		AnimationController::SwapClips();
		tCurrent = zeroTime;
		controlTimer = 0;
	}

	this->intervalTimer.Toc();
	this->intervalTimer.Tic();

	CameraManager::UpdateCamera();

	AnimationController::ProcessAnimation(tCurrent);

	AnimationController::UpdateSkeleton(pFirstBone, tCurrent);

	GameObjectMan::Update(this->globalTimer.Toc());

	//PhysicsObjectMan::Update(this->globalTimer.Toc());

	deltaTime = animSpeed* Time(Time::NTSC_30_FRAME);
	Time maxTime;

	tCurrent += deltaTime;

	AnimationController::FindMaxTime(maxTime);

	// protection for time values for looping
	if (tCurrent < Time(Time::ZERO))
	{
		tCurrent = maxTime;
	}
	else if (tCurrent > maxTime)
	{
		tCurrent = Time(Time::ZERO);
	}
	else
	{
		// do nothing
	}


	controlTimer++;
	//

}

 
void Game::Draw()
{
	GameObjectMan::Draw();
	//PhysicsObjectMan::Draw();
}

void Game::UnLoadContent()
{

}

void Game::ClearBufferFunc()
{
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, Colors_gl::glDarkSlateGray); //<--change background color
	glClearBufferfv(GL_DEPTH, 0, &one);
}
