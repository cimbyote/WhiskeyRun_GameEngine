#include <assert.h>

#include "sb7.h"
#include "Game.h"
#include "Mouse.h"


extern Game *pGame;


Mouse::Mouse()
{

}

// Use this to read mouse buttons
bool Mouse::GetKeyState(AZUL_MOUSE button)
{
	bool value;

	if (pGame->GetMouseButton(button) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}
	return value;
}

void Mouse::GetCursor(float &xPos, float &yPos)
{
	// get mouse position
	pGame->GetCursorPos(xPos, yPos);

}