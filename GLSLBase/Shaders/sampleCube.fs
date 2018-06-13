#version 330

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Pos;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

const float c_ambient = 0.2; //ȯ�汤�� 0.2��ŭ ������ ��ħ
const float c_diffuse = 0.7;
const float c_specular = 0.5;

void main()
{
//v_Pos ���� �ε�ġ�� ��ǥ(���� ��ǥ)
	vec3 lightDir = normalize(u_lightPos - v_Pos);
	vec3 viewDir = normalize(u_cameraPos - v_Pos);  
	vec3 reflectDir = reflect(-lightDir, v_Normal);

	float diffuse = max(0, dot(lightDir, v_Normal)) * c_diffuse;
	float specular = pow(max(0, dot(viewDir, reflectDir)), 128) * c_specular;
	//pow(����)�� �Ҽ��� ����� �𿩼� ������� ������ (������ ������ = �ݻ縧 ���� like ö)
	float ambient = 1.0 * c_ambient;

    FragColor.rgb = (ambient + diffuse + specular) * v_Color.rgb;
	FragColor.a = v_Color.a;
}
