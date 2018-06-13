/*
Copyright 2018 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer *g_Renderer = NULL;

float g_time = 0.0f;
float mouseX, mouseY;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.f);
	//g_Renderer->fillAll(0, 0, 0, 0.1f);
	// Renderer Test
	//g_Renderer->Test();
	//g_Renderer->Lecture3();
	/*
	g_time += 0.01f;*/
	//float tmp[] = {
	//	-1,1,
	//	1,1,
	//	0,0,
	//	-1,-1,
	//	1,-1
	//};
	//g_time += 0.01f;
	//g_time += 0.01f;
	//g_Renderer->TargetPaticle(0, -1, 0, 1, g_time);
	//g_Renderer->vertexAnimation();
	//g_Renderer->Raider();
	//g_Renderer->FragmentAni(g_mouseInput, g_time);
	//g_Renderer->textureTest();
	//g_Renderer->drawBMPTexture();
	//g_Renderer->paticleAnimation();
	//g_Renderer->renderCube();
	g_Renderer->renderTest();
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	float xPos = ((float)x - 250.f) / 250.f;
	float yPos = -((float)y - 250.f) / 250.f;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseX = x;
		mouseY = y;
	}

	RenderScene();
}

void MouseMove(int x, int y)
{
	float valx = (x - mouseX) * 0.01f;
	float valy = (y - mouseY)* 0.01f;

	mouseX = x;
	mouseY = y;

	glm::vec3 rot = glm::vec3(valy, valx, 0);
	g_Renderer->rotateModel(rot);
}

void KeyInput(unsigned char key, int x, int y)
{
	glm::vec3 move = glm::vec3(0);
	glm::vec3 rot = glm::vec3(0);
	float val = 0.f;
	switch (key) {
	case 'W':
		move.z -= 0.5f;
		break;
	case 'S':
		move.z += 0.5f;
		break;
	case 'A':
		move.x -= 0.5f;
		break;
	case 'D':
		move.x += 0.5f;
		break;
	case 'Z':
		rot.x += 0.5f;
		break;
	case 'X':
		rot.y += 0.5;
		break;
	case 'C':
		rot.z += 0.5f;
		break;
	case 'Q':
		val -= 0.1f;
		break;
	case 'E':
		val += 0.1f;
		break;
	}
	g_Renderer->moveModel(move);
	g_Renderer->rotateModel(rot);
	g_Renderer->scalingModel(val);
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("GLSL KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

