
#type vertexShader
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;

out vec3 v_Normal;
out vec3 v_WorldPos;
out vec2 v_TexCoord;

void main()
{
    vec4 worldPos = u_ModelMatrix * vec4(aPos, 1.0);
    v_WorldPos = worldPos.xyz;

    // 法线矩阵（处理缩放）
    mat3 normalMatrix = transpose(inverse(mat3(u_ModelMatrix)));
    v_Normal = normalize(normalMatrix * aNormal);

    v_TexCoord = aTexCoord;

    gl_Position = u_ViewProjectionMatrix * worldPos;
}

#type fragmentShader
#version 460 core

in vec3 v_Normal;
in vec3 v_WorldPos;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;

// 方向光参数
uniform float u_DirectionalLightIntensity;
uniform vec3 u_DirectionalLightColor;
uniform vec3 u_DirectionalLightDirection;

void main()
{
    // 纹理颜色
    vec4 texColor = texture(u_Texture, v_TexCoord);
    vec3 albedo = texColor.rgb;
    float alpha = texColor.a;

    vec3 N = normalize(v_Normal);
    vec3 L = normalize(-u_DirectionalLightDirection); // 光照指向物体

    // 环境光
    vec3 ambient = 0.1 * albedo;

    // 漫反射（Lambert）
    float NdotL = max(dot(N, L), 0.0);
    vec3 diffuse = NdotL * albedo * u_DirectionalLightColor;

    vec3 color = ambient + diffuse * u_DirectionalLightIntensity;

    FragColor = vec4(color, alpha);
}
