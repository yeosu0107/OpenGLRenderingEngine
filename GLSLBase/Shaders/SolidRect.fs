#version 330

layout(location=0) out vec4 FragColor;

//in vec4 v_Color;
//in float v_value;
in vec2 v_value;

uniform float gScale;

void main()
{
	//¿Ô´Ù°¬´Ù
	//FragColor = v_Color;
	//float ka=(sin(gScale)+1.0)/2.0;
	//if(v_value>ka-0.1 && v_value<ka+0.1)
		//FragColor=vec4(1);
	//else
		//FragColor=vec4(0);

	//FragColor=vec4(1);
	float len=(v_value.x * v_value.x) + (v_value.y * v_value.y);
	
	if(len<0.25*gScale && len>0.23*gScale)
		FragColor=vec4(1,1,1,1);
	else
		FragColor=vec4(0,0,0,0);
}
