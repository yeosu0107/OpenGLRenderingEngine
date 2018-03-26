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
	//메인메모리상에 버텍스 데이터 생성
	float vertices[] = { 
		0.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 1.0f, 0.0f, 1.0f};
	//버퍼오브젝트 생성하고 아이디 부여
	glGenBuffers(1, &m_Lecture3);
	//Array 데이터를 저장한다고 명시
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	//GPU상의 메모리에 데이터를 복사
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//여기까지 완료하면 데이터 준비 끝

	float color[] = {
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f };
	//버퍼오브젝트 생성하고 아이디 부여
	glGenBuffers(1, &m_Lecture2);
	//Array 데이터를 저장한다고 명시
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//GPU상의 메모리에 데이터를 복사
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	//여기까지 완료하면 데이터 준비 끝

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
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
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
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
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
	//ARRAY 형태를 사용할 것이라고 명시 & 아이디값
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//Draw시 데이터를 읽어갈 단위 (어디서부터 어디까지 읽을건지 등...)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//그려라!
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetAttribLocation(m_SolidRectShader, "a_Color");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "gScale");
	//셰이더 코드, 셰이더 코드 인풋 레이아웃

	glEnableVertexAttribArray(id0);
	//ARRAY 형태를 사용할 것이라고 명시 & 아이디값
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture3);
	//Draw시 데이터를 읽어갈 단위 (어디서부터 어디까지 읽을건지 등...)
	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(id1);
	//ARRAY 형태를 사용할 것이라고 명시 & 아이디값
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture2);
	//Draw시 데이터를 읽어갈 단위 (어디서부터 어디까지 읽을건지 등...)
	glVertexAttribPointer(id1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glUniform1f(id2, scale);
	if (scale > 1.0f || scale < -1.0f)
		tmp *= -1;
	scale += 0.02f*tmp;
		

	//그려라!
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Lecture4()
{
	glUseProgram(m_SolidRectShader);

	GLint id0 = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint id1 = glGetUniformLocation(m_SolidRectShader, "gPos");
	GLint id2 = glGetUniformLocation(m_SolidRectShader, "gScale");

	glEnableVertexAttribArray(id0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lecture4);
	glVertexAttribPointer(id0, 4, GL_FLOAT, GL_FALSE, 0, 0);


	glUniform1f(id1, pos);
	if (pos >= 0.5f || pos <= -0.5f)
		tmp *= -1;
	pos += 0.02f*tmp;

	glUniform1f(id2, scale);
	if (scale > 1.0f || scale < -1.0f)
		tm2 *= -1;
	scale += 0.05f*tm2;

	/*glUniform1f(id3, scale);
	if (pos >= 0.4f || pos <= -0.4f) {
		if (tmp < 0)
			scale -= 0.1f;
		else
			scale += 0.1f;
	}*/


	//그려라!
	glDrawArrays(GL_LINES, 0, 3);
}
