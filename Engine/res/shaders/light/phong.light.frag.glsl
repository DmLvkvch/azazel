#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct Material {
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D u_texture_0;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

uniform Material u_material;
uniform Light light;

void main()
{
    float ambientStrength = 0.1;
    vec3 lightColor = u_material.color;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(u_lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff;  
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(lightDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = lightColor * spec * u_material.color;

    vec3 result = (ambient + diffuse + specular) * texture2D(u_texture_0, texCoord).rgb;
    gl_FragColor = vec4(result, 1.0);
}