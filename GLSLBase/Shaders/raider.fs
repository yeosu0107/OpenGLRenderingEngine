#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos; //25만개의 출력이 잘 보간되어 넘어옴

const float PI = 3.141592;

uniform vec2 u_target[3];
uniform float time;

void main()
{
	float len = 0;
	float weight = 0;
	for(int i = 0; i<3; ++i) {
		len = length(v_Pos - u_target[i]);
		if(len<0.02) 
			weight+=0.3f;
	}

	vec2 center=vec2(0);
	float newTime = fract(time/2)*2;
	float circleLen = length(v_Pos - center);
	float finalColor=0;

	if(circleLen > newTime - 0.02 && circleLen < newTime + 0.02) 
		finalColor = 1*weight + 0.2f;
	else
		discard;
	FragColor=vec4(finalColor);
}

