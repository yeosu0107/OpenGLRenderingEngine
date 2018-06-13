#version 330

in vec4 a_Position;

uniform float time;
uniform vec2 startPoint;
uniform vec2 endPoint;


const float PI = 3.141592;

void main()
{
	vec2 nowPos=vec2(-10.0f, -10.0f);

	vec2 k = endPoint-startPoint; //방향벡터
	
	mat2 rot = mat2(cos(PI/2), sin(PI/2), -sin(PI/2), cos(PI/2));
	vec2 verti = normalize(rot * k);

	if(time>a_Position.x) {
		float newTime = time - a_Position.x;
		newTime=fract(newTime/2); //0~1 사이

		float tmp=sin(newTime * PI * a_Position.y) * a_Position.z * 0.5;

		nowPos = startPoint + k * newTime;
		nowPos += verti * tmp;
	}

	float zValue=a_Position.z;
	gl_Position=vec4(
	nowPos.x, 
	nowPos.y, 
	zValue, 
	1.0f	);

	gl_PointSize = 10;
}
