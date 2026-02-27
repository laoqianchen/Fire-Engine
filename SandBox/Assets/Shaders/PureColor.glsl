
#type vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(aPos, 1.0);
}

#type fragmentShader
#version 460 core
out vec4 FragColor;
		
uniform vec4 u_Color;

void main()
{
	FragColor = u_Color;
}