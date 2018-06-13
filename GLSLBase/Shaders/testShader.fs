#version 330

in vec2 v_Pos;
//in float v_GrayScale;

out vec4 FragColor;

uniform sampler2D u_tex;


void main()
{
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//FragColor = vec4(v_GrayScale, v_GrayScale, v_GrayScale, 1.0);

	//float xPos = v_Pos.x;
	//float yPos = v_Pos.y;
	///////////////////////////////////////////////////////
	//float len = sqrt(xPos*xPos + yPos*yPos);

	//if(len<0.5)
		//FragColor=vec4(1.0, 0.0, 0.0, 1.0);
	//else
		//FragColor=vec4(0.0, 0.0, 0.0, 1.0);

	//if(v_GrayScale >= 0.5)
		//FragColor=vec4(1.0, 0.0, 0.0, 1.0);
	//else
		//FragColor=vec4(0.0, 0.0, 0.0, 1.0);
		///////////////////////////////////////////////////////
	//float val = v_GrayScale * 7;
	//val = floor(val)/6;
	//FragColor = vec4(val, 0, 0, 1.0);

	//FragColor = vec4(1.0, 0, 0, 1.0);

	FragColor = texture(u_tex, v_Pos);
}
