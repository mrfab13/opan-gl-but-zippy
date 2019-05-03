#include "ObjectManager.h"

Input input1;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

glm::vec3 ObjectManager::GetObjectPos()
{
	return (objPos);
}

void ObjectManager::SetObjectPos(glm::vec3 temp)
{
	objPos = temp;
}

void ObjectManager::initializeObjPos()
{
	objPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void ObjectManager::movement(Audio1& audio2, GLfloat deltaTime, float screenW, float screenH)
{
	const float speed = 5.0f;
	glm::vec3 temp;
	temp = GetObjectPos();

	if (input1.CheckKeyDown('w') == true)
	{

		if (temp.y < ((screenH -100)/2))
		{
			temp.y += speed * deltaTime;
			SetObjectPos(temp);
			audio2.playSound(2);
		}

	}
	if (input1.CheckKeyDown('a') == true)
	{
		if (temp.x > (0 - ((screenW - 100) / 2)))
		{
			temp.x -= speed * deltaTime;
			SetObjectPos(temp);
			audio2.playSound(2);
		}
	}
	if (input1.CheckKeyDown('s') == true)
	{
		if (temp.y > (0 - ((screenH - 100) / 2)))
		{
			temp.y -= speed * deltaTime;
			SetObjectPos(temp);
			audio2.playSound(2);
		}
	}
	if (input1.CheckKeyDown('d') == true)
	{
		if (temp.x < ((screenW - 100) / 2))
		{
			temp.x += speed * deltaTime;
			SetObjectPos(temp);
			audio2.playSound(2);
		}
	}
}



