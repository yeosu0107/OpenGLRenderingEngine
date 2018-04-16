#version 330

in vec4 a_Position;
in vec4 a_Color;

uniform float move;
uniform vec2 startPoint;
uniform vec2 endPoint;

out vec4 v_Color;

const float PI = 3.141592;

void main()
{
	vec2 nowPos=vec2(-10.0f, -10.0f);
	float xValue=-10.0f;
	float yValue=-10.0f;
	//float xValue=a_Position.x;
	//float yValue=sin(a_Position.x * PI*3 + move) * 0.2f  * (a_Position.x-1);

	vec2 velocity=normalize( endPoint-startPoint); //속도
	vec2 base=vec2(1,0);

	float tmp=dot(velocity, base);
	float magA=sqrt( velocity.x*velocity.x + velocity.y*velocity.y );
	float magB=sqrt(base.x*base.x + base.y * base.y);
	tmp=tmp/(magA*magB);
	float angle=acos(tmp);
	mat2 rotMat= mat2(cos(angle), sin(angle), -sin(angle), cos(angle));

	float cosA=cos(tmp);
	float sinA=sin(angle);


	if(move>a_Position.x) {
		float newTime = move - a_Position.x;
		newTime=fract(newTime/2); //0~1 사이

		vec2 rotPos=vec2(0, (sin(newTime * PI * a_Position.y) * a_Position.z * 0.2));
		rotPos*=rotMat;
		//otPos.x=cosA*rotPos.x - sinA*rotPos.y;
		//rotPos.y=sinA*rotPos.x + cosA*rotPos.y;

		nowPos=startPoint + rotPos + velocity * newTime;

		//시작점 + 속도 * 시간 = s=s0 + v*t
		//nowPos.x= startPoint.x + velocity.x * newTime;
		//nowPos.y= startPoint.y + velocity.y* newTime + (sin(newTime * PI * a_Position.y) * a_Position.z * 0.2);
	}

	//사인 내부 = 주기, 폭, 가중치
	//가중치 -> 오른쪽으로 갈수록 폭이 넓어짐 (왼쪽 -1+1 = 0, 오른쪽 1+1=2)
	float zValue=a_Position.z;
	gl_Position=vec4(
	nowPos.x, //-1~1
	nowPos.y, 
	zValue, 
	1.0f	);
	v_Color = a_Color;
}
