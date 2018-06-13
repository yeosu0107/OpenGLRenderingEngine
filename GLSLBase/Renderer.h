#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\euler_angles.hpp"

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
	void textureTest();
	void multiTextureSampling();
	void multiTextureSampling2();
	void drawBMPTexture();
	void vertexAnimation();
	void paticleAnimation();

	void renderCube();

	void moveModel(glm::vec3 move);
	void rotateModel(glm::vec3 rot);
	void scalingModel(float val);

	void renderTest();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);
	GLuint CreatePngTexture(char * filePath);
	void LoadTextureFromBmp(const char* path, GLuint& texture);

	void CreateVertexBufferObjects();		
	void targetPaticleBufferObjects();
	void fragmentAniBufferObjects();
	void textureSamplingBufferObjects();
	void raiderBufferObjects();
	void fillBufferObjcects();
	void textureTestBufferObjects();
	void multiTextureBufferObjects();
	void multiTextureBufferObjects2();
	void LoadTextureBufferObject();
	void VertexAnimationBufferObject();
	void paticleAnimationBufferObject();

	void InitializeCamera();
	void InitalizeTransform();
	void updateTransformMatrix();
	void cubeBufferObject();

	void testBufferObjects();

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
	GLuint m_textureTest = 0;
	GLuint m_multiTexture = 0;
	GLuint m_paticleTexture = 0;
	GLuint m_vertexAniShader = 0;
	GLuint m_paticleAnimationShader = 0;
	GLuint m_Shader_Proj = 0;

	GLuint m_testShader = 0;

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
	GLuint m_simileRect = 0;
	GLuint m_smileTexture = 0;
	GLuint m_multiSmile[6] = { 0, };
	GLuint m_multiSmile2 = 0;
	GLuint m_bmpTexture[2] = { 0, };
	GLuint m_triangles = 0;
	GLuint VBO_ParticleMesh = 0;
	GLuint gParticleTextureID = 0;

	GLuint m_VBO_Cube = 0;

	GLuint m_testObjects = 0;

	GLuint gDummyVertexCount = 0;
	GLuint gParticleVertexCount = 0;
	float scale = 0.0f;
	float tmp = 1.0f;
	float tm2 = 1.0f;
	float pos = 0.0f;

	float m_xPos, m_yPos;
	int animation = 0;

	glm::vec3 m_v3Camera_Position;
	glm::vec3 m_v3Camera_Lookat;
	glm::vec3 m_v3Camera_Up;

	glm::mat4 m_m4OrthoProj;
	glm::mat4 m_m4Proj;
	glm::mat4 m_m4View;
	glm::mat4 m_m4ProjView;

	glm::vec3 m_v3modelTranslation;
	glm::vec3 m_v3modelRotation;
	glm::vec3 m_v3modelScaling;

	glm::mat4 m_m4modelTranslation;
	glm::mat4 m_m4modelRotation;
	glm::mat4 m_m4modelScaling;
	glm::mat4 m_m4modelMatrix;
};

