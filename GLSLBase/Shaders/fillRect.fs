#version 330

layout(location=0) out vec4 FragColor;

uniform vec4 v_Color;

void main()
{
	FragColor=v_Color;
}

