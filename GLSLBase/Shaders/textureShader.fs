#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Tex;

uniform sampler2D uTex;


void main()
{
	//FragColor = texture(uTex, v_Tex);

	//FragColor = texture(uTex, fract(v_Tex * 2));

	//float tx = fract(v_Tex.x *2);
	//float ty = v_Tex.y * 0.5f + (1-floor(v_Tex.x * 2))*0.5f;
	//FragColor = texture(uTex, vec2(tx, ty));
	//시험에 꼭나옴
	float tx = fract(v_Tex.x * 3);
	float ty = v_Tex.y*0.33f + (2-floor(v_Tex.x*3))*0.33f;
	FragColor = texture(uTex, vec2(tx, ty));
}

