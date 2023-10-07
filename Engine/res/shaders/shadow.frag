#version 450 core

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 normal; 
layout(location = 2) in vec2 texCoords; 
layout(location = 3) in vec4 fragPosLightSpace; 

layout(binding = 0) uniform sampler2D u_texture_0;
layout(binding = 1) uniform sampler2D shadowMap;

layout (binding = 0) uniform UBO
{
    vec3 lightPos;
    vec3 viewPos;
} ubo;

layout (location = 0) out vec4 frag_color;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    vec3 normal = normalize(normal);
    vec3 lightDir = normalize(ubo.lightPos - fragPos);
    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}  

void main()
{           
    vec3 color = texture(u_texture_0, texCoords).rgb;
    vec3 normal = normalize(normal);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    // ambient
    vec3 ambient = 0.15 * lightColor;
    // diffuse
    vec3 lightDir = normalize(ubo.lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(ubo.viewPos - fragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    frag_color = vec4(lighting, 1.0);
}