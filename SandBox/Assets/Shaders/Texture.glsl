#type vertexShader
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = aTexCoord;
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(aPos, 1.0);
}

#type fragmentShader
#version 460 core
out vec4 FragColor;
			
in vec2 v_TexCoord;
			
uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord);
}