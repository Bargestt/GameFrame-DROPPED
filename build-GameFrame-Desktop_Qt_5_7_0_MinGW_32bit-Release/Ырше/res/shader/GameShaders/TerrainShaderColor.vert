#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 tColor;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 projectionview;
uniform mat4 view;

uniform mat3 normalMat;

void main()
{
    //vec4 pos = model*vec4(aPos, 1.0);
    gl_Position = projectionview*model*vec4(aPos, 1.0);
    tColor = aColor;

    FragPos = vec3(view *model*vec4(aPos, 1.0));
    Normal =  normalMat * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0));
}
