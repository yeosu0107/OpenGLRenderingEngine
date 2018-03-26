#version 330

layout(location=0) out vec4 FragColor;

//in vec4 v_Color;
in float v_value;

uniform float gScale;

void main()
{
	//FragColor = v_Color;
	float ka=(sin(gScale)+1.0)/2.0;
	if(v_value>ka-0.1 && v_value<ka+0.1)
		FragColor=vec4(1);
	else
		FragColor=vec4(0);
}
