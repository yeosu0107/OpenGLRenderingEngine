#version 330

in vec4 a_Position;
in vec2 a_Tex;

out vec2 v_Tex;

void main()
{
	gl_Position = a_Position;
	v_Tex=a_Tex;
}
