#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Tex;

uniform sampler2D uTex;


void main()
{
	//FragColor=vec4(v_Tex, 0, 1);
	//FragColor = texture(uTex, fract(v_Tex * 3));
	FragColor = texture(uTex, v_Tex * 3);
}

