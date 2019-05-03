#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <freeglut.h>


class camera
{
public:
	camera();
	~camera();
	void initializeCamera();
	void calculate(GLfloat currentTime);
	glm::mat4 getView();

private:

	glm::vec3 camPos;
	glm::vec3 camLookDir;
	glm::vec3 camUpDir;

	glm::mat4 rotMat;
	glm::vec4 newPos;
	
	//view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);
	glm::mat4 view;
	glm::vec3 camTar;

};