#include "Game.h"

#include "MemTracker.h"

Game *pGame = 0;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	MEM_TRACKER_BEGIN
	pGame = new Game("WhiskeyRun", 1280, 720);
	pGame->Run();

	return 0;
}