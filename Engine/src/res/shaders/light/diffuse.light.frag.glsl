#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture_0;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(0.0745, 0.6275, 0.8824);
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.0745, 0.6275, 0.8824);   
    vec4 result = vec4(diffuse + ambient, 1.0) * texture(texture_0, texCoord);
    gl_FragColor = result;
}