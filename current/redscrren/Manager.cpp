#include "Manager.h"

GLfloat manager::GetSCREEN_H()
{
	return (SCREEN_H);
}

GLfloat manager::GetSCREEN_W()
{
	return (SCREEN_W);
}

void manager::SetScreenDimentions(int axis, int size)
{
	if (axis == 1)
	{
		SCREEN_W = size;
	}
	else if (axis == 2)
	{
		SCREEN_H = size;
	}
}
