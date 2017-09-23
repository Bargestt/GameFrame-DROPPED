#version 330 core
in vec3 tColor;
in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

uniform vec3 lightColor;

uniform sampler2D texture1;

void main()
{
//    float ambientStrength = 0.3;
//    vec3 ambient = ambientStrength * lightColor;


//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(LightPos - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;


    // specular
//    float specularStrength = 0.5;
//    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;

    //vec3 result = (ambient + diffuse/*+specular*/)*tColor;

//    vec3 result = tColor;
//    FragColor = vec4(result, 0.3);

    vec4 color = texture(texture1, TexCoord);
    if(color.a <0.1) discard;

    FragColor = color;
}
