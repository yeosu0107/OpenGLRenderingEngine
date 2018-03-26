#version 330

in vec4 a_Position;
in vec4 a_Color;

uniform float gPos;
uniform float gScale;

out vec2 v_value;

void main()
{
	//gl_Position = vec4(a_Position, 1);
	//gl_Position = a_Position + vec4(gPos, 0, 0, 0);
	gl_Position.xyz = a_Position.xyz;
	gl_Position.w = 1.0;

	//v_Color=a_Color;
	v_value=a_Position.xy; //vs output
}
