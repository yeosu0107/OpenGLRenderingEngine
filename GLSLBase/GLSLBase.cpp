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
float g_mouseInput[10];
int    g_mouse = 0;

void RenderScene(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	g_Renderer->fillAll(0, 0, 0, 0.1);
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
	//g_time += 0.1f;
	g_time += 0.01f;
	//g_Renderer->TargetPaticle(0, 0, 1, 1, g_time);
	g_Renderer->Raider();
	//g_Renderer->FragmentAni(g_mouseInput, g_time);
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
	g_mouseInput[g_mouse] = xPos;
	g_mouseInput[g_mouse + 1] = yPos;
	g_mouse += 2;
	if (g_mouse >= 10)
		g_mouse = 0;
	//g_Renderer->InputPos(xPos, yPos);
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
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
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

