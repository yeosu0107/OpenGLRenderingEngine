#version 330

in vec2 vTexPos;
in float valpha;
in vec3 v_velocity;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vTexPos);
	FragColor.w *= valpha;
	FragColor.xyz += v_velocity.xyz;
}
