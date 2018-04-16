#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos; //25������ ����� �� �����Ǿ� �Ѿ��

const float PI = 3.141592;

void main()
{
	float x=v_Pos.x;
	float y=v_Pos.y;

	float sinx = pow (sin(x * PI * 5), 30);
	float siny = pow (sin(y * PI * 5), 30);

	FragColor=vec4(sinx , siny, siny + sinx, 1);
}

