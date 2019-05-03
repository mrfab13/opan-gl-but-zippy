#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <windows.h>
#include <fmod.hpp>
#include "ShaderLoader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Manager.h"
#include "TextLabel.h"

using namespace std;

ShaderLoader m_shader;

GLuint program = NULL;

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint texture;
GLuint texture1;
GLfloat currentTime;
GLfloat pasttime = glutGet(GLUT_ELAPSED_TIME);
GLfloat deltaTime;


Audio1 audio;
Input input;
camera camera1;
ObjectManager objectmanager;
manager manager1;
TextLabel label1; //score
TextLabel label2; //actual score
TextLabel label3; //menu
TextLabel label4; //sub menu

float TotalScore =  0.0f;
bool startplay = false;
bool restartplay = true;
int menuno = 0;
glm::mat4 proj;


GLfloat vertices[]
{	//pos                    //colour
	-0.5f,	-0.5f,	0.0f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,//bot left
	0.5f,	0.5f,	0.0f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,// top right
	-0.5f,	0.5f,	0.0f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f, //top left
	0.5f,	-0.5f,	0.0f,	 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, //bot right
};

GLuint indices[] = 
{
	0,1,2,	//1 
	0,3,1,	//2
};


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (input.CheckKeyDown('o') == true)
	{
		startplay = false;
		restartplay = true;
	}


	if (restartplay == true)
	{
		TotalScore = 0.0f;

		if (menuno == 0)
		{
			input.inputdelay(input);
			if (input.CheckKeyDown('o') == true && input.checkDownFirst(input, 'o') == true)
			{
				menuno = 1;
			}
			if (input.CheckKeyDown('p') == true)
			{
				startplay = true;
				restartplay = false;
			}
			if (input.CheckKeyDown('q') == true)
			{
				glutLeaveMainLoop();
			}
			label3.Render();
		}
		else if (menuno == 1)
		{
			label4.Render();
			input.inputdelay(input);
			if (input.CheckKeyDown('o') == true && input.checkDownFirst(input, 'o') == true)
			{
				menuno = 0;
			}
		}
		else
		{

		}



	}


	if (startplay == true)
	{
		label1.Render();
		label2.Render();
		//timer/score
		TotalScore = TotalScore + deltaTime;
		int displayScore = TotalScore;
		label2.SetText(to_string(displayScore));

		glUseProgram(program);

		objectmanager.movement(audio, deltaTime, manager1.GetSCREEN_W(), manager1.GetSCREEN_H());
		camera1.calculate(currentTime);
		//movement
		glm::vec3 objPosition = glm::vec3(0.5f, 0.5f, 0.0f);
		objPosition += objectmanager.GetObjectPos();

		glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);

		glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
		float rotationAngle = 0;
		glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

		glm::vec3 objscale = glm::vec3(100.0f, 100.0f, 100.0f);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objscale);

		glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;

		glm::mat4 mvp = proj * camera1.getView() * model;
		GLuint mvpLoc = glGetUniformLocation(program, "mvp");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));


		//picture
		GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");//gluint?
		glUniform1f(currentTimeLoc, currentTime);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(program, "Tex"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(program, "Tex1"), 1);


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update()
{
	audio.update();
	

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - pasttime) *0.1f;
	pasttime = currentTime;

	glutPostRedisplay();

}

int main(int argc, char **argv) 
{

	manager1.SetScreenDimentions(1, 1280);
	manager1.SetScreenDimentions(2, 720);

	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);

	glutInitWindowSize(manager1.GetSCREEN_W(), manager1.GetSCREEN_H());
	glutCreateWindow("(0) : error C5145: must write to gl_Position");
	
	if (glewInit() != GLEW_OK)
	{
		cout << "somthin wrong cheif" << endl;
		system("pause");
	}

	//proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HIGHT, 0.1f, 100.0f);
	float halfw = (float)manager1.GetSCREEN_W() * 0.5f;
	float halfh = (float)manager1.GetSCREEN_H() * 0.5f;
	proj = glm::ortho( -halfw, halfw, -halfh, halfh, 0.1f, 100.0f);



	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

	label1 = TextLabel(manager1, "score:", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));
	label2 = TextLabel(manager1, "", "ass/fonts/comic.ttf", glm::vec2(-400.0f, 300.0f));
	label3 = TextLabel(manager1, R"(idk:the game 
press p to play 
press q to quit 
press o for other)", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));
	label4 = TextLabel(manager1, R"(use WASD to move
 
game created by vaughan webb 
song used: The Son of Flynn - Daft Punk 
press o to return to main menu )", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));



	program = ShaderLoader::CreateProgram("shader.vs", "shader.fs");




	
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	int width, height;
	unsigned char* image = SOIL_load_image("ass/pics/doge.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image2 = SOIL_load_image("ass/pics/garf3.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0 ,3 ,GL_FLOAT ,GL_FALSE , (8 * (sizeof(GLfloat))), (GLvoid*) 0 );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(3 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, (8*(sizeof(GLfloat))), (GLvoid*)(6 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(2);

	camera1.initializeCamera();

	// sound
	audio.AudioInit();
	audio.Create("ass/sounds/Tron Legacy - Soundtrack OST - 03 The Son of Flynn - Daft Punk.mp3", 1);
	audio.Create("ass/Sounds/Thump.wav", 2);
	audio.playSound(1);

	//main loop
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);

	glutSpecialFunc(Input::specialCharDown);
	glutSpecialUpFunc(Input::specialCharUp);

	glutMainLoop();
	return 0;
}


