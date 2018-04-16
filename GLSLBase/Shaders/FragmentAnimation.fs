#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos; //25만개의 출력이 잘 보간되어 넘어옴

const float PI = 3.141592;

void main()
{
	float x=v_Pos.x;
	float y=v_Pos.y;

	float sinx = pow (sin(x * PI * 5), 30);
	float siny = pow (sin(y * PI * 5), 30);

	FragColor=vec4(sinx , siny, siny + sinx, 1);
}

