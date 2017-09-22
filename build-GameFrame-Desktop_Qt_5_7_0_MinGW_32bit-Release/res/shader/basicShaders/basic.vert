#version 330 core
layout (location = 0) in vec3 aPos;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projectionview;

void main()
{
    //
    gl_Position = projectionview*model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
