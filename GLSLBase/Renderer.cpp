#include "stdafx.h"
#include "Renderer.h"

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
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	
	//Create VBOs
	CreateVertexBufferObjects();

	if (m_SolidRectShader > 0 && m_VBORect > 0)
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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::Test()
{
	float newX, newY;

	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

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
	if (scale > 1.0f || scale < -1.0f)
		tmp *= -1;
	scale += 0.02f*tmp;
		

	//�׷���!
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture4()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetUniformLocation(m_SolidRectShader, "gPos");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "gScale");

	//�Դٰ��� �ڵ�
	//glEnableVertexAttribArray(id0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	//glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);


	//glUniform1f(id1, pos);
	//if (pos >= 0.5f || pos <= -0.5f)
	//	tmp *= -1;
	//pos += 0.02f*tmp;

	//glUniform1f(id2, scale);
	//if (scale > 1.0f || scale < -1.0f)
	//	tm2 *= -1;
	//scale += 0.05f*tm2;

	//���׸���
	glEnableVertexAttribArray(id0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(id0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//�׷���!
	//glDrawArrays(GL_LINES, 0, 3);
}
