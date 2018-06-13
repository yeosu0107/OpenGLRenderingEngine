#version 330

in vec3 Position;
//in float GrayScale;
in vec2 texPos;

out vec2 v_Pos;
//out float v_GrayScale;

void main()
{
    gl_Position = vec4(Position, 1.0);
	//v_GrayScale = GrayScale;
	v_Pos = texPos;
}
