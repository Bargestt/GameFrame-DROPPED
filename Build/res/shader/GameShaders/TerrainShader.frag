#version 330 core
in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

uniform sampler2D texture1;

uniform vec3 lightColor;



void main()
{
    //vec3 texColor = vec3(0.2, 0.5, 0.2);

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;


    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;


    // specular
//    float specularStrength = 0.5;
//    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse/*+specular*/)*texture(texture1, TexCoord).rgb;
    FragColor = vec4(result, 1.0);
}
