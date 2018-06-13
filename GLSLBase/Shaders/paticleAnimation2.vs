#version 330

in vec3 Position;
in vec2 TexPos;
in vec4 Velocity;

uniform float uTime;

out vec2 vTexPos;
out float valpha;
out vec3 v_velocity;

const vec3 gravity = vec3(0, -0.4, 0);

void main()
{
	
	float time = uTime - Velocity.w;
	vec3 newPos = vec3(-1000,-1000,-1000);
	float alpha = 1.0;
	if(time > 0) {
		time = fract(time / 3) * 3;
		alpha = 1 - fract(time / 3);

		newPos = Position.xyz + 
			time * Velocity.xyz + 
			0.5 * gravity * time * time;
	}
    gl_Position = vec4(newPos, 1.0);

	vTexPos = TexPos;
	valpha = alpha;
	v_velocity = Velocity.xyz + gravity * time;
}
