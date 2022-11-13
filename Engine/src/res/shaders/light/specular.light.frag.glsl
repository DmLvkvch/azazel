#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D u_texture_0;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 lightColor = vec3(0.0745, 0.6275, 0.8824);
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;   
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(lightDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec4 result = vec4(diffuse + ambient + specular, 1.0) * texture(u_texture_0, texCoord);
    gl_FragColor = result;
}