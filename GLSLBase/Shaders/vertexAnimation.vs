#version 330

in vec3 a_Position;

uniform float u_time;

out float color;
out vec2 v_Position;

const float PI = 3.141592;
uniform mat4 u_ProjView;

void main()
{
	float xPos	= a_Position.x;
	//float yPos	= a_Position.y + sin((xPos + 0.5)  * PI * 2 + u_time) * 0.5 ;
	float yPos = a_Position.y;
	float zPos = a_Position.z + sin((xPos + 0.5)  * PI * 2 + u_time) * 0.5 ;

	gl_Position = u_ProjView * vec4(xPos, yPos, zPos, 1.0);

	color = yPos - a_Position.y;
	v_Position = a_Position.xy + vec2(0.5, 0.5); // x,y가 0~1 사이로 넘어감
}
