#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 tColor;
out vec2 TexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform mat3 normalMat;
uniform float time;

void main()
{

    //vec4 pos = model*vec4(aPos, 1.0);
    gl_Position = projection*view*model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    tColor = vec3(0.3,0.7,1.0);
    TexCoord = vec2( (aPos.x + 1.0) /2.0, (aPos.z + 1.0) /2.0);;


//    FragPos = vec3(view *model*vec4(aPos, 1.0));
//    Normal =  normalMat * aNormal;
//    LightPos = vec3(view * vec4(lightPos, 1.0));
}
