#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D u_texture_0;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    float ambientStrength = 0.1;
    vec3 lightColor = material.ambient * vec3(0.0745, 0.6275, 0.8824);
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);  
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(lightDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);

    ambient  = light.ambient * material.ambient;
    diffuse  = light.diffuse * (diff * material.diffuse);
    specular = light.specular * (spec * material.specular); 

    vec4 result = vec4(diffuse + ambient + specular, 1.0) * texture(u_texture_0, texCoord);
    gl_FragColor = result;
}