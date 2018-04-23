#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Pos; //25������ ����� �� �����Ǿ� �Ѿ��

uniform float time;

uniform vec2 centerPos[5];

const float PI = 3.141592;

void main()
{
	//float x=v_Pos.x + 1;
	//float y=v_Pos.y;

	//�����׸�Ʈ ���� 
	//float sinx = pow (sin(x * PI * 5), 30);
	//float siny = pow (sin(y * PI * 5), 30);
	//FragColor=vec4(sinx , siny, siny + sinx, 1);

	//���׸���
	//float len = x*x + y*y;
	//if(len <=1 && len>=0.8)
		//FragColor=vec4(1,1,1,1);
	//else
		//FragColor=vec4(0,0,0,1);

	//sin� �ִϸ��̼�
	//float xValue = (x + time) * PI;
	//if(sin(xValue)*0.5 + 0.05>y && sin(xValue)*0.5-0.05<y)
		//FragColor=vec4(1,1,1,1);
	//else
		//FragColor=vec4(0,0,0,1);

	//����
	FragColor=vec4(0);
	vec2 center = vec2(0); //���������� �߽ɺ�
	vec2 pos = v_Pos;
	float len=0;
	for(int i=0; i<5; ++i) {
		center=centerPos[i];
		len = length(pos - center) * 2 * PI;
		FragColor +=vec4(sin(len*5 - time) * clamp(1-len/(2*PI),0,1));
	}
}

