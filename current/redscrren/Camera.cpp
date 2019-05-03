#include "Camera.h"
#include "glm.hpp"
#include <iostream>
#include <freeglut.h>

camera::camera()
{
}

camera::~camera()
{
}

void camera::initializeCamera()
{
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


}

void camera::calculate(GLfloat currentTime)
{
	
	//rotMat = glm::rotate(glm::mat4(), glm::radians(50.0f * currentTime), glm::vec3(0, 1, 0));
	newPos = /*rotMat **/ glm::vec4(0, 0, 3, 1);
	camPos = glm::vec3(newPos);
	camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::lookAt(camPos, camTar, camUpDir);

}

glm::mat4 camera::getView()
{
	return (view);
}



