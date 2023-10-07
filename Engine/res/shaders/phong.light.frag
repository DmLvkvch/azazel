#version 450 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 fragPos;

struct Material {
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

layout(binding = 0) uniform sampler2D u_texture_0;

layout (binding = 0) uniform UBO 
{
    uniform vec3 u_viewPos;

    uniform Material u_material;
    uniform Light u_light;
} ubo;

layout(location = 0) out vec4 frag_color;

void main()
{
    // ambient
    vec3 ambient = ubo.u_light.ambient * ubo.u_material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(ubo.u_light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = ubo.u_light.diffuse * diff * ubo.u_material.diffuse;
    
    // specular
    vec3 viewDir = normalize(ubo.u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.u_material.shininess);
    vec3 specular = ubo.u_light.specular * spec * ubo.u_material.specular;  
        
    vec3 result = ambient + diffuse + specular;
    frag_color = texture(u_texture_0, texCoord) * vec4(result, 1.0);
}