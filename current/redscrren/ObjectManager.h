#pragma once

#include <freeglut.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"


class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager();
	glm::vec3 GetObjectPos();
	void SetObjectPos(glm::vec3);
	void initializeObjPos();
	void movement(Audio1& audio2, GLfloat deltaTime, float ScreenW, float screenH);

private:
	glm::vec3 objPos;
};