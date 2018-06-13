#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Tex;

uniform float time;

uniform sampler2D uTexSlot1;
uniform sampler2D uTexSlot2;
uniform sampler2D uTexSlot3;


void main()
{
	//FragColor=vec4(v_Tex, 0, 1);
	//FragColor = texture(uTex, fract(v_Tex * 3));
	//FragColor = texture(uTex, v_Tex * 3);
	float size = 10;
	float sheer = 0.5;
	float tx = fract(v_Tex.x*size + sheer * floor(v_Tex.y*size) );
	float ty = fract(v_Tex.y*size);

	vec4 t1 = texture(uTexSlot1, v_Tex).bgra;
	vec4 t2 = texture(uTexSlot2, vec2(tx, ty)).bgra;

	//float newX = v_Tex.x * 3.141592 * 2;
	//float newY = v_Tex.y * 2 - 1;

	//if(sin(newX) > newY) 
		//FragColor = t1;
	//else 
		//FragColor = t2;
	
	//FragColor = t2;
	FragColor = t2;

	//float newnewY = v_Tex.y * 3.141592 * 100 + time;
	//float grayScale = sin(newnewY);

	//FragColor *= abs(vec4(pow(grayScale,7)));
	//FragColor = t1 + t2;
}

