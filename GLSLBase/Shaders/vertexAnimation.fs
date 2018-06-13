#version 330

in float color;
in vec2 v_Position;

layout(location=0) out vec4 FragColor;

uniform sampler2D uTex;

void main()
{
	vec4 tex = texture(uTex, v_Position).bgra;
	FragColor = tex;
	FragColor=vec4(tex.x + color, tex.y + color, tex.z + color, 1.0);
}

