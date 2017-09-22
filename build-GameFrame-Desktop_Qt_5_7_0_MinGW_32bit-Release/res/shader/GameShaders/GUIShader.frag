#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform mat4 projection;
void main()
{
    vec4 color = texture(texture1, TexCoord);
    if(color.a <0.1) discard;


    FragColor = color;
}
