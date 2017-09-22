#version 330 core
layout (location = 0) in vec2 aPos;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, 0.0, 1.0);

    TexCoord = vec2( (aPos.x + 1.0) /2.0, (aPos.y + 1.0) /2.0);;
}
