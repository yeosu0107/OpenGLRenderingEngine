#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void Test();

	void InputPos(float x, float y) {
		m_xPos = x;
		m_yPos = y;
	}

	void Lecture2();
	void Lecture3();
	void Lecture4();
	void Lecture5();
	void Lecture6();
	void TargetPaticle(float sx, float sy, float tx, float ty, float time);
	void FragmentAni(float* centers, float time);
	void Raider();
	void fillAll(float r, float g, float b, float a);
	void textureSampling();
private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();		
	void targetPaticleBufferObjects();
	void fragmentAniBufferObjects();
	void textureSamplingBufferObjects();
	void raiderBufferObjects();
	void fillBufferObjcects();
	

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_targetPaticleShader = 0;
	GLuint m_FragmentAniShader = 0;
	GLuint m_raiderShader = 0;
	GLuint m_fillShader = 0;
	GLuint m_textureSampling = 0;

	GLuint m_Lecture2 = 0;
	GLuint m_Lecture3 = 0;
	GLuint m_Lecture4 = 0;
	GLuint m_Lecture6 = 0;
	GLuint m_Lecture7 = 0;
	GLuint m_tri= 0;
	GLuint m_col = 0;
	GLuint m_tricol = 0;
	GLuint m_raider = 0;
	GLuint m_fillrect = 0;
	GLuint m_fragAni = 0;
	GLuint m_rect = 0;
	GLuint m_texture = 0;


	float scale = 0.0f;
	float tmp = 1.0f;
	float tm2 = 1.0f;
	float pos = 0.0f;

	float m_xPos, m_yPos;
};

