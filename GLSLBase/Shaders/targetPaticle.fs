#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D uTex;

void main()
{
	FragColor= texture(uTex, gl_PointCoord);
}

