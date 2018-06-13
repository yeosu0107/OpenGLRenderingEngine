#version 330

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_Pos;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_cameraPos;

const float c_ambient = 0.2; //환경광은 0.2만큼 영향을 미침
const float c_diffuse = 0.7;
const float c_specular = 0.5;

void main()
{
//v_Pos 빛이 부딛치는 좌표(월드 좌표)
	vec3 lightDir = normalize(u_lightPos - v_Pos);
	vec3 viewDir = normalize(u_cameraPos - v_Pos);  
	vec3 reflectDir = reflect(-lightDir, v_Normal);

	float diffuse = max(0, dot(lightDir, v_Normal)) * c_diffuse;
	float specular = pow(max(0, dot(viewDir, reflectDir)), 128) * c_specular;
	//pow(제곱)을 할수록 가운데로 모여서 밝아지고 좁아짐 (제곱을 많이함 = 반사름 잘함 like 철)
	float ambient = 1.0 * c_ambient;

    FragColor.rgb = (ambient + diffuse + specular) * v_Color.rgb;
	FragColor.a = v_Color.a;
}
