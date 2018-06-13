#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Tex;

uniform sampler2D uTex;

uniform float yPos;

void main()
{
	float tx = v_Tex.x;
	float ty = yPos/6 + v_Tex.y / 6;
	FragColor = texture(uTex, vec2(tx, ty));

	//FragColor = texture(uTex, fract(v_Tex * 2));
}

