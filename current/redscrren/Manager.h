#pragma once
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include "gtc/type_ptr.hpp"

class manager
{
public:
	GLfloat GetSCREEN_H();
	GLfloat GetSCREEN_W();
	void SetScreenDimentions(int axis, int size);

private:

	GLfloat SCREEN_H;
	GLfloat SCREEN_W;


};