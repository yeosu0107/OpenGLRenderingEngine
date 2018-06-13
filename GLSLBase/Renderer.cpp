#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/Lecture06.vs", "./Shaders/Lecture06.fs");
	m_targetPaticleShader = CompileShaders("./Shaders/targetPaticle.vs", "./Shaders/targetPaticle.fs");
	m_FragmentAniShader= CompileShaders("./Shaders/FragmentAnimation.vs", "./Shaders/FragmentAnimation.fs");
	m_raiderShader = CompileShaders("./Shaders/raider.vs", "./Shaders/raider.fs");
	m_fillShader = CompileShaders("./Shaders/fillRect.vs", "./Shaders/fillRect.fs");
	m_textureSampling = CompileShaders("./Shaders/textureSampling.vs", "./Shaders/textureSampling.fs");
	m_textureTest = CompileShaders("./Shaders/textureShader.vs", "./Shaders/textureShader.fs");
	m_multiTexture = CompileShaders("./Shaders/multiTexture.vs", "./Shaders/multiTexture.fs");
	m_vertexAniShader = CompileShaders("./Shaders/vertexAnimation.vs", "./Shaders/vertexAnimation.fs");
	m_paticleAnimationShader = CompileShaders("./Shaders/paticleAnimation2.vs", "./Shaders/paticleAnimation2.fs");
	m_Shader_Proj = CompileShaders("./Shaders/sampleCube.vs", "./Shaders/sampleCube.fs");
	m_testShader = CompileShaders("./Shaders/testShader.vs", "./Shaders/testShader.fs");

	//Create VBOs
	targetPaticleBufferObjects();
	fragmentAniBufferObjects();
	raiderBufferObjects();
	fillBufferObjcects();
	textureSamplingBufferObjects();
	textureTestBufferObjects();
	multiTextureBufferObjects();
	multiTextureBufferObjects2();
	LoadTextureBufferObject();
	VertexAnimationBufferObject();
	paticleAnimationBufferObject();
	testBufferObjects();

	InitializeCamera();
	InitalizeTransform();
	cubeBufferObject();

	if (m_SolidRectShader > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-0.5, -0.5, 0.f, -0.5, 0.5, 0.f, 0.5, 0.5, 0.f, //Triangle1
		-0.5, -0.5, 0.f,  0.5, 0.5, 0.f, 0.5, -0.5, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);


	//Lecture03
	//���θ޸𸮻� ���ؽ� ������ ����
	float vertices[] = { 
		0.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 1.0f, 0.0f, 1.0f};
	//���ۿ�����Ʈ �����ϰ� ���̵� �ο�
	glGenBuffers(1, &m_Lecture3);
	//Array �����͸� �����Ѵٰ� ���
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	//GPU���� �޸𸮿� �����͸� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//������� �Ϸ��ϸ� ������ �غ� ��

	float color[] = {
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f };
	//���ۿ�����Ʈ �����ϰ� ���̵� �ο�
	glGenBuffers(1, &m_Lecture2);
	//Array �����͸� �����Ѵٰ� ���
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//GPU���� �޸𸮿� �����͸� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	//������� �Ϸ��ϸ� ������ �غ� ��

	//Lecture04
	float vertices2[] = {
		-0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 1.0f
	};
	glGenBuffers(1, &m_Lecture4);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//Lecture05
	float Position[9] = { 
		0.0, 1.0, 0.0, 
		-1.0, -1.0, 0.0, 
		1.0, -1.0, 0.0 
	};
	float Colors[12] = { 
		1.0, 1.0, 1.0, 1.0, 
		1.0, 0.0, 0.0, 1.0, 
		0.0, 0.0, 1.0, 1.0 
	};
	float PositionColor[] = { 
		0.0, 1.0, 0.0, 1.0f, 1.0, 1.0, 1.0, 1.0, 
		-1.0, -1.0, 0.0, 1.0f,  1.0, 0.0, 0.0, 1.0, 
		1.0, -1.0, 0.0, 1.0f, 0.0, 0.0, 1.0, 1.0 
	};

	glGenBuffers(1, &m_tri);
	glBindBuffer(GL_ARRAY_BUFFER, m_tri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Position), Position, GL_STATIC_DRAW);

	glGenBuffers(1, &m_col);
	glBindBuffer(GL_ARRAY_BUFFER, m_col);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

	glGenBuffers(1, &m_tricol);
	glBindBuffer(GL_ARRAY_BUFFER, m_tricol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PositionColor), PositionColor, GL_STATIC_DRAW);

	//Lecture06
	const int max = 500;
	float *testPosition = new float[(max+1)*4];
	for (int i = 0; i < max; ++i) {
		//testPosition[i * 4] = (2.0f * (float)i / (float)max)- 1.0f;
		testPosition[i * 4] = (2.0f * (float)i / (float)max);
		//testPosition[i * 4 + 1] = 0.0f;
		testPosition[i * 4 + 1] = (float)rand() / float(RAND_MAX);
		testPosition[i * 4 + 2] = (float)rand() / float(RAND_MAX);
		//testPosition[i *4 + 2] = 0.0f;
		testPosition[i *4 + 3] = 1.0f;
		if ((float)rand() / float(RAND_MAX) > 0.5f)
			testPosition[i * 4+2] *= -1.0f;
	}
	glGenBuffers(1, &m_Lecture6);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*(max+1), testPosition, GL_STATIC_DRAW);
}

void Renderer::targetPaticleBufferObjects()
{
	//
	const int max = 500;
	float *testPosition = new float[(max) * 4];
	for (int i = 0; i < max; ++i) {
		testPosition[i * 4 + 0] = (float)i / (float)max * 2;					//start time
		testPosition[i * 4 + 1] = (float)rand() / float(RAND_MAX);	//period
		testPosition[i * 4 + 2] = (float)rand() / float(RAND_MAX);	//width
		testPosition[i * 4 + 3] = 1.0f;
		if ((float)rand() / float(RAND_MAX) > 0.5f)
			testPosition[i * 4 + 2] *= -1.0f;
	}
	glGenBuffers(1, &m_Lecture6);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * (max), testPosition, GL_STATIC_DRAW);

	m_paticleTexture = CreatePngTexture("./Texture/paticle.png");
}

void Renderer::fragmentAniBufferObjects()
{
	float rect[]
		=
	{
		-1.0, -1.0, 0.f, -1.0, 1.0, 0.f, 1.0, 1.0, 0.f, //Triangle1
		-1.0, -1.0, 0.f,  1.0, 1.0, 0.f, 1.0, -1.0, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_fragAni);
	glBindBuffer(GL_ARRAY_BUFFER, m_fragAni);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
}

void Renderer::textureSamplingBufferObjects()
{
	float size = 0.5f;
	float rect[] = 
	{
		-size, size, 0.0f, 0.0f, 1.0f,		//x,y,z,s,t
		-size, -size, 0.0f, 0.0f, 0.0f,
		size, size, 0.0f, 1.0f, 1.0f,
		size, size, 0.0f , 1.0f, 1.0f,
		-size, -size, 0.0f , 0.0f, 0.0f,
		size, -size, 0.0f , 1.0f, 0.0f
	};

	static const GLulong checkerboard[] =
	{
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenBuffers(1, &m_rect);
	glBindBuffer(GL_ARRAY_BUFFER, m_rect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
	//�ؽ���, ����(0), ���ͳ�����RGBA,s��ũ��, t��ũ��, 0, ���� (RGBA), ä�δ�ũ��, �ȼ��� ������
	
	//���ε� �� �ؽ��� �����Ϳ� �÷��� �ο�, ���ε� �Ŀ� �ؾ� ��
	//GL_NEAREST (�ؽ��� �� ��ó ��ǥ�� ������)
	//GL_LINEAR (���̰��� ���������̼��ؼ� �־���, ������ ���������� ����Ƽ�� ����)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void Renderer::raiderBufferObjects()
{
	float rect[]
		=
	{
		-1.0, -1.0, 0.f, -1.0, 1.0, 0.f, 1.0, 1.0, 0.f, //Triangle1
		-1.0, -1.0, 0.f,  1.0, 1.0, 0.f, 1.0, -1.0, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_raider);
	glBindBuffer(GL_ARRAY_BUFFER, m_raider);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
}

void Renderer::fillBufferObjcects()
{
	float rect[]
		=
	{
		-1.0, -1.0, 0.f, -1.0, 1.0, 0.f, 1.0, 1.0, 0.f, //Triangle1
		-1.0, -1.0, 0.f,  1.0, 1.0, 0.f, 1.0, -1.0, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_fillrect);
	glBindBuffer(GL_ARRAY_BUFFER, m_fillrect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
}

void Renderer::textureTestBufferObjects()
{
	float size = 0.5f;
	float rect[] =
	{
		-size, size, 0.0f, 0.0f, 1.0f,		//x,y,z,s,t
		-size, -size, 0.0f, 0.0f, 0.0f,
		size, size, 0.0f, 1.0f, 1.0f,
		size, size, 0.0f , 1.0f, 1.0f,
		-size, -size, 0.0f , 0.0f, 0.0f,
		size, -size, 0.0f , 1.0f, 0.0f
	};
	GLulong textureSmile[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	glGenBuffers(1, &m_simileRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	glGenTextures(1, &m_smileTexture);
	glBindTexture(GL_TEXTURE_2D, m_smileTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::multiTextureBufferObjects()
{
	float size = 0.5f;
	float rect[] =
	{
		-size, size, 0.0f, 0.0f, 1.0f,		//x,y,z,s,t
		-size, -size, 0.0f, 0.0f, 0.0f,
		size, size, 0.0f, 1.0f, 1.0f,
		size, size, 0.0f , 1.0f, 1.0f,
		-size, -size, 0.0f , 0.0f, 0.0f,
		size, -size, 0.0f , 1.0f, 0.0f
	};
	GLulong textureSmile[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	GLulong textureSmile1[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	GLulong textureSmile2[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	GLulong textureSmile3[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	GLulong textureSmile4[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	GLulong textureSmile5[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	GLulong** textures;
	textures = new GLulong*[6];
	textures[0] = textureSmile;
	textures[1] = textureSmile1;
	textures[2] = textureSmile2;
	textures[3] = textureSmile3;
	textures[4] = textureSmile4;
	textures[5] = textureSmile5;


	glGenBuffers(1, &m_simileRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	for (int i = 0; i < 6; ++i) {
		glGenTextures(1, &m_multiSmile[i]);
		glBindTexture(GL_TEXTURE_2D, m_multiSmile[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	
}

void Renderer::multiTextureBufferObjects2()
{
	float size = 0.5f;
	float rect[] =
	{
		-size, size, 0.0f, 0.0f, 1.0f,		//x,y,z,s,t
		-size, -size, 0.0f, 0.0f, 0.0f,
		size, size, 0.0f, 1.0f, 1.0f,
		size, size, 0.0f , 1.0f, 1.0f,
		-size, -size, 0.0f , 0.0f, 0.0f,
		size, -size, 0.0f , 1.0f, 0.0f
	};

	GLulong textureSmileTotal[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenBuffers(1, &m_simileRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	glGenTextures(1, &m_multiSmile2);
	glBindTexture(GL_TEXTURE_2D, m_multiSmile2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 48, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmileTotal);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::LoadTextureBufferObject()
{
	float size = 0.5f;
	float rect[] =
	{
		-size, size, 0.0f, 0.0f, 1.0f,		//x,y,z,s,t
		-size, -size, 0.0f, 0.0f, 0.0f,
		size, size, 0.0f, 1.0f, 1.0f,
		size, size, 0.0f , 1.0f, 1.0f,
		-size, -size, 0.0f , 0.0f, 0.0f,
		size, -size, 0.0f , 1.0f, 0.0f
	};

	glGenBuffers(1, &m_simileRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	LoadTextureFromBmp("./Texture/texture2.bmp", m_bmpTexture[0]);
	LoadTextureFromBmp("./Texture/texture3.bmp", m_bmpTexture[1]);
}

void Renderer::VertexAnimationBufferObject()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 32;
	int pointCountY = 32;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	gDummyVertexCount = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, m_triangles);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* gDummyVertexCount * 3, vertices, GL_STATIC_DRAW);

}

void Renderer::paticleAnimationBufferObject()
{

	int particleCount = 500;
	float particleSize = 0.05f;
	float particleInitPosX = (rand() / (float)RAND_MAX - 0.5) * 0.2f;
	float particleInitPosY = (rand() / (float)RAND_MAX - 0.5) * 0.2f;

	float* particleVertices = new float[particleCount * 2 * 3 * (3 + 2 + 4)];
	int particleFloatCount = particleCount * 2 * 3 * (3 + 2 + 4);
	gParticleVertexCount = particleCount * 2 * 3;

	int particleVertIndex = 0;

	for (int i = 0; i < particleCount; i++)
	{
		particleInitPosX = (rand() / (float)RAND_MAX - 0.5f) * 2;
		particleInitPosY = (rand() / (float)RAND_MAX);

		float randomValueX = 0.f;
		float randomValueY = 0.f;
		float randomValueZ = 0.f;
		float randomStartTime = 0.f;
		float velocityScale = 0.1f;

		randomValueX = (rand() / (float)RAND_MAX - 0.5)*velocityScale;
		randomValueY = (rand() / (float)RAND_MAX - 0.5)*velocityScale;
		randomValueZ = 0.f;
		randomStartTime = (rand() / (float)RAND_MAX)*20.f;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;

		particleVertices[particleVertIndex] = -particleSize / 2.f + particleInitPosX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = particleSize / 2.f + particleInitPosY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 0.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = 1.f;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueX;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueY;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomValueZ;
		particleVertIndex++;
		particleVertices[particleVertIndex] = randomStartTime;
		particleVertIndex++;
	}

	glGenBuffers(1, &VBO_ParticleMesh);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ParticleMesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*particleFloatCount, particleVertices, GL_STATIC_DRAW);



	GLulong textureParticle[]
		=
	{
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xFFFFFF00, 0x00000000, 0x00000000,
		0x00000000, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0x00000000,
		0x00000000, 0x00000000, 0xFFFFFF00, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	};
	glGenTextures(1, &gParticleTextureID);
	glBindTexture(GL_TEXTURE_2D, gParticleTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 5, 5, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureParticle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


}

void Renderer::InitializeCamera()
{
	m_v3Camera_Position = glm::vec3(0.f, 0.f, 5.f);
	m_v3Camera_Lookat = glm::vec3(0.0f, 0.0f, 0.0f);
	m_v3Camera_Up = glm::vec3(0.0f, 1.f, 0.0f);

	m_m4View = glm::lookAt(m_v3Camera_Position, m_v3Camera_Lookat, m_v3Camera_Up);

	m_m4OrthoProj = glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.f, 2.f);
	m_m4Proj  = glm::perspectiveFovRH(45.f, (float)m_WindowSizeX, (float)m_WindowSizeY, 0.f, 10.f);
	m_m4ProjView = m_m4Proj * m_m4View;
}

void Renderer::InitalizeTransform()
{
	m_v3modelTranslation = glm::vec3(0.f, 0.f, 0.f);
	m_v3modelRotation = glm::vec3(0.f, 0.f, 0.f);
	m_v3modelScaling = glm::vec3(1.f, 1.f, 1.f);

	updateTransformMatrix();
}

void Renderer::updateTransformMatrix()
{
	m_m4modelTranslation = glm::translate(glm::mat4(1.f), m_v3modelTranslation);
	m_m4modelRotation = glm::eulerAngleXYZ(m_v3modelRotation.x, m_v3modelRotation.y, m_v3modelRotation.z);
	m_m4modelScaling = glm::scale(glm::mat4(1.f), m_v3modelScaling);

	m_m4modelMatrix = m_m4modelTranslation * m_m4modelRotation * m_m4modelScaling;
}

void Renderer::cubeBufferObject()
{

	float temp = 0.5f;

	float cube[] = {
		-temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
		-temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
		-temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
		temp, -temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f,
		temp, temp, temp, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, // first face : R

		temp, -temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
		temp, temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
		temp, -temp, temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, -temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f,
		temp, temp, -temp, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, //second face : G

		-temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		-temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		-temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		temp, temp, -temp, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 1.f, //third face : B

		-temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		-temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
		temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
		-temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
		temp, temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f,
		temp, -temp, -temp, 0.f, 0.f, -1.f, 1.f, 1.f, 0.f, 1.f, //fourth face : R+G (yellow)

		-temp, -temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
		-temp, temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
		-temp, temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
		-temp, -temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
		-temp, temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f,
		-temp, -temp, -temp, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, // fifth face : R+B (purple)

		-temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
		temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
		temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
		-temp, -temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a 
		-temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
		temp, -temp, -temp, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f, 1.f, //sixth face : G+B (Cyan)
	};

	glGenBuffers(1, &m_VBO_Cube);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);


}

void Renderer::testBufferObjects()
{
	float vertices[30] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f

	};

	glGenBuffers(1, &m_testObjects);
	glBindBuffer(GL_ARRAY_BUFFER, m_testObjects);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLulong textureSmile[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::moveModel(glm::vec3 move)
{
	m_v3modelTranslation += move;
}

void Renderer::rotateModel(glm::vec3 rot)
{
	m_v3modelRotation += rot;
}

void Renderer::scalingModel(float val)
{
	m_v3modelScaling += glm::vec3(val, val, val);
}

void Renderer::renderTest()
{
	GLuint shader = m_testShader;
	glUseProgram(shader);

	int uniformTex = glGetUniformLocation(shader, "u_tex");

	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);


	int attributePos = glGetAttribLocation(shader, "Position");
	//int grayScale = glGetAttribLocation(shader, "GrayScale");
	int texPos = glGetAttribLocation(shader, "texPos");

	glEnableVertexAttribArray(attributePos);
	glEnableVertexAttribArray(texPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_testObjects);
	glVertexAttribPointer(attributePos, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
	glVertexAttribPointer(texPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int & outWidth, unsigned int & outHeight)
{
	printf("Reading image %s\n", imagepath);
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = nullptr;
	fopen_s(&file, imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	return data;

}

GLuint Renderer::CreatePngTexture(char * filePath)
{
	GLuint temp;
	glGenTextures(1, &temp);
	//Load Pngs
	// Load file and decode image.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return temp;
}

void Renderer::LoadTextureFromBmp(const char* path, GLuint& texture)
{
	unsigned int width, height;
	unsigned char* bmp_texture = loadBMPRaw(path, width, height);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::Test()
{
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	//ARRAY ���¸� ����� ���̶�� ��� & ���̵�
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//Draw�� �����͸� �о ���� (��𼭺��� ������ �������� ��...)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//�׷���!
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "gScale");
	//���̴� �ڵ�, ���̴� �ڵ� ��ǲ ���̾ƿ�

	glEnableVertexAttribArray(id0);
	//ARRAY ���¸� ����� ���̶�� ��� & ���̵�
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	//Draw�� �����͸� �о ���� (��𼭺��� ������ �������� ��...)
	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(id1);
	//ARRAY ���¸� ����� ���̶�� ��� & ���̵�
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//Draw�� �����͸� �о ���� (��𼭺��� ������ �������� ��...)
	glVertexAttribPointer(id1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(id2, scale);
	if (scale > 1.0f || scale < 0.1f)
		tmp *= -1;

	//�׷���!
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture4()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetUniformLocation(m_SolidRectShader, "gColor");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "gScale");

	//���׸���
	glEnableVertexAttribArray(id0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(id2, scale);
	if (scale > 1.0f || scale < 0.0f)
		tm2 *= -1;
	scale += 0.01f*tm2;
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//�׷���!
	//glDrawArrays(GL_LINES, 0, 3);
}

void Renderer::Lecture5()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	////���� �׸���
	//glBindBuffer(GL_ARRAY_BUFFER, m_tri);
	//glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	////��Ʈ����ƮID, ������(���), ����, �븻������ ����, ��Ʈ���̵�(�ǳʶٴ� ����), ������������
	//glBindBuffer(GL_ARRAY_BUFFER, m_col);
	//glVertexAttribPointer(id1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//��ŷ�ؼ� �ѹ��� �׸���
	glBindBuffer(GL_ARRAY_BUFFER, m_tricol);
	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0); 
	//ó������ 3���� �а�, ���� ���� ó������ 7��° ��
	glVertexAttribPointer(id1, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(4*sizeof(float)));
	//ó������ 3���ǳʶ� 4��°���� 4���� �а�, �������� ���������� 7��° ��

	glDrawArrays(GL_TRIANGLES, 0, 3); //���, ����������, ����
}

void Renderer::Lecture6()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "move");
	GLint id3= glGetUniformLocation(m_SolidRectShader, "startPoint");
	GLint id4 = glGetUniformLocation(m_SolidRectShader, "endPoint");

	glEnableVertexAttribArray(id0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture6);

	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(id2, scale);
	scale += 0.05f;

	glUniform2f(id3, 0.0f, 0.0f); //����
	glUniform2f(id4, m_xPos, m_yPos);


	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::TargetPaticle(float sx, float sy, float tx, float ty, float time)
{
	GLuint shader = m_targetPaticleShader;
	glUseProgram(shader);

	GLint id0 = glGetAttribLocation(shader, "a_Position");
	GLint id2 = glGetUniformLocation(shader, "time");
	GLint id3 = glGetUniformLocation(shader, "startPoint");
	GLint id4 = glGetUniformLocation(shader, "endPoint");
	GLint texture = glGetUniformLocation(shader, "uTex");

	glEnableVertexAttribArray(id0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture6);

	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(id2, time);
	glUniform2f(id3, sx, sy);	//������
	glUniform2f(id4, tx, ty);	//����

	
	glUniform1i(texture, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_paticleTexture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);
	glDrawArrays(GL_POINTS, 0, 500);
}

void Renderer::FragmentAni(float* centers, float time) //input 5
{
	GLuint shader = m_FragmentAniShader;
	glUseProgram(shader);

	GLint id0 = glGetAttribLocation(shader, "a_Position");
	GLint id1 = glGetUniformLocation(shader, "time");
	GLint id2 = glGetUniformLocation(shader, "centerPos");

	glEnableVertexAttribArray(id0);

	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUniform1f(id1, time);

	glUniform2fv(id2, 5, centers);

	glDisableVertexAttribArray(id0);
}

void Renderer::Raider()
{
	GLuint shader = m_raiderShader;

	GLfloat target[] = {
		0.3f, 0.3f, -0.4f, 0.5f, 0.6f, -0.8f
	};

	glUseProgram(shader);


	GLint id0 = glGetAttribLocation(shader, "a_Position");
	GLint id1 = glGetUniformLocation(shader, "u_target");
	GLint id2 = glGetUniformLocation(shader, "time");

	glEnableVertexAttribArray(id0);
	glBindBuffer(GL_ARRAY_BUFFER, m_raider);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUniform2fv(id1, 3, target);
	scale += 0.01f;
	glUniform1f(id2, scale);

	glDisableVertexAttribArray(id0);
}

void Renderer::fillAll(float r, float g, float b, float a)
{
	GLuint shader = m_fillShader;

	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint id0 = glGetAttribLocation(shader, "a_Position");
	GLint id1 = glGetUniformLocation(shader, "v_Color");
	glEnableVertexAttribArray(id0);
	glBindBuffer(GL_ARRAY_BUFFER, m_fillrect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUniform4f(id1, r, g, b, a);

	glDisableVertexAttribArray(id0);

	glDisable(GL_BLEND);
}

void Renderer::textureSampling()
{
	GLuint m_shader = m_textureSampling;
	glUseProgram(m_shader);

	GLint id0 = glGetAttribLocation(m_shader, "a_Position");
	GLint id1 = glGetAttribLocation(m_shader, "a_Tex");
	GLint id2 = glGetUniformLocation(m_shader, "uTex");

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	//��ŷ�ؼ� �ѹ��� �׸���
	glBindBuffer(GL_ARRAY_BUFFER, m_rect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(id1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	//x,y,z,s,t,		x,y,z,s,t
	//���� 5, ������ 0 & 3
	//������ float �̹Ƿ� sizeof(float) ������
	//id, �о�� ����, ����, false, ����, ������)

	glUniform1i(id2, 0);
	//0������ ����ϰڴ�
	glActiveTexture(GL_TEXTURE0);
	//0������ Ȱ��ȭ
	glBindTexture(GL_TEXTURE_2D, m_texture);
	//�ش�Ǵ� ���Կ� �ؽ��İ� ���ε�

	glDrawArrays(GL_TRIANGLES, 0, 6); //���, ����������, ����
}

void Renderer::textureTest()
{
	GLuint m_shader = m_textureTest;
	glUseProgram(m_shader);

	GLint id0 = glGetAttribLocation(m_shader, "a_Position");
	GLint id1 = glGetAttribLocation(m_shader, "a_Tex");
	GLint id2 = glGetUniformLocation(m_shader, "uTex");

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(id1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glUniform1i(id2, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_smileTexture);

	glDrawArrays(GL_TRIANGLES, 0, 6); //���, ����������, ����
}

void Renderer::multiTextureSampling()
{
	GLuint m_shader = m_multiTexture;
	glUseProgram(m_shader);

	GLint id0 = glGetAttribLocation(m_shader, "a_Position");
	GLint id1 = glGetAttribLocation(m_shader, "a_Tex");
	GLint id2 = glGetUniformLocation(m_shader, "uTex");

	auto p = GL_TEXTURE0;
	for (int i = 0; i < 6; ++i) {
		glActiveTexture(p);
		glBindTexture(GL_TEXTURE_2D, m_multiSmile[i]);
		p += 1;
	}
	

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(id1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glUniform1i(id2, scale);

	scale += 0.1f * tmp;
	if (scale >= 5.5 || scale <= 0)
		tmp *= -1.0f;
	

	glDrawArrays(GL_TRIANGLES, 0, 6); //���, ����������, ����
}

void Renderer::multiTextureSampling2()
{
	GLuint m_shader = m_multiTexture;
	glUseProgram(m_shader);

	GLint id0 = glGetAttribLocation(m_shader, "a_Position");
	GLint id1 = glGetAttribLocation(m_shader, "a_Tex");
	GLint id2 = glGetUniformLocation(m_shader, "uTex");
	GLint id3 = glGetUniformLocation(m_shader, "yPos");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_multiSmile2);

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(id1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glUniform1i(id2, 0);
	glUniform1f(id3, (float)(scale));
	scale += 1.0f * tmp;
	if (scale >= 5 || scale <= 0)
		tmp *= -1.0f;
	glDrawArrays(GL_TRIANGLES, 0, 6); //���, ����������, ����
}

void Renderer::drawBMPTexture()
{
	GLuint m_shader = m_textureSampling;
	glUseProgram(m_shader);

	GLint id0 = glGetAttribLocation(m_shader, "a_Position");
	GLint id1 = glGetAttribLocation(m_shader, "a_Tex");
	GLint id2 = glGetUniformLocation(m_shader, "uTexSlot1");
	GLint id3 = glGetUniformLocation(m_shader, "uTexSlot2");
	GLint id4 = glGetUniformLocation(m_shader, "time");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_bmpTexture[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_bmpTexture[1]);

	glEnableVertexAttribArray(id0);
	glEnableVertexAttribArray(id1);

	glBindBuffer(GL_ARRAY_BUFFER, m_simileRect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(id1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glUniform1i(id2, 0);
	glUniform1i(id3, 1);

	glUniform1f(id4, scale);
	scale += 0.1f;
	
	glDrawArrays(GL_TRIANGLES, 0, 6); //���, ����������, ����
}

void Renderer::vertexAnimation()
{
	GLuint m_shader = m_vertexAniShader;
	glUseProgram(m_shader);

	int attrribPosition = glGetAttribLocation(m_shader, "a_Position");
	int uniformPos = glGetUniformLocation(m_shader, "u_time");
	GLint id2 = glGetUniformLocation(m_shader, "uTex");

	GLuint projView = glGetUniformLocation(m_shader, "u_ProjView");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_m4ProjView[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_bmpTexture[0]);

	scale += 0.01f;
	glUniform1f(uniformPos, scale);

	glEnableVertexAttribArray(attrribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_triangles);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1i(id2, 0);

	glDrawArrays(GL_TRIANGLES, 0, gDummyVertexCount);
}

void Renderer::paticleAnimation()
{
	GLuint gShaderProgram = m_paticleAnimationShader;
	glUseProgram(gShaderProgram);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int uniformTime = glGetUniformLocation(gShaderProgram, "uTime");
	glUniform1f(uniformTime, scale);
	scale += 0.001;

	int uniformTexture = glGetUniformLocation(gShaderProgram, "uTexture");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gParticleTextureID);
	glUniform1i(uniformTexture, 0);

	int attrribPosition = glGetAttribLocation(gShaderProgram, "Position");
	int attrribTexPos = glGetAttribLocation(gShaderProgram, "TexPos");
	int attrribVelocity = glGetAttribLocation(gShaderProgram, "Velocity");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);
	glEnableVertexAttribArray(attrribVelocity);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ParticleMesh);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(attrribVelocity, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(5 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, gParticleVertexCount);

	glDisableVertexAttribArray(attrribPosition);
	glDisableVertexAttribArray(attrribTexPos);
	glDisableVertexAttribArray(attrribVelocity);

	glDisable(GL_BLEND);
}

void Renderer::renderCube()
{
	GLuint shader = m_Shader_Proj;

	glUseProgram(shader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);

	updateTransformMatrix();

	GLuint projView = glGetUniformLocation(shader, "u_ProjView");
	GLuint modelMatrix = glGetUniformLocation(shader, "u_Model");
	GLuint rotationMatirx = glGetUniformLocation(shader, "u_Rotation");
	GLuint cameraPos = glGetUniformLocation(shader, "u_cameraPos");
	GLuint lightPos = glGetUniformLocation(shader, "u_lightPos");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_m4ProjView[0][0]);
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &m_m4modelMatrix[0][0]);
	glUniformMatrix4fv(rotationMatirx, 1, GL_FALSE, &m_m4modelRotation[0][0]);
	glUniform3f(lightPos, 0, 0, 2);
	glUniform3f(cameraPos, m_v3Camera_Position.x, m_v3Camera_Position.y, m_v3Camera_Position.z);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	int attribNormal = glGetAttribLocation(shader, "a_Normal");
	int attribColor = glGetAttribLocation(shader, "a_Color");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribNormal);
	glEnableVertexAttribArray(attribColor);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribNormal);
	glDisableVertexAttribArray(attribColor);
}
