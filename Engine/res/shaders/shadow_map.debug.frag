#version 450 core

layout(location = 0) in vec2 texCoords;

layout(binding = 0) uniform sampler2D depthMap;

layout (binding = 0) uniform UBO
{
    float near_plane;
    float far_plane;
} ubo;

layout(location = 0) out vec4 frag_color;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * ubo.near_plane * ubo.far_plane) / (ubo.far_plane + ubo.near_plane - z * (ubo.far_plane - ubo.near_plane));	
}

void main()
{             
    float depthValue = texture(depthMap, texCoords).r;
    frag_color = vec4(vec3(LinearizeDepth(depthValue) / ubo.far_plane), 1.0);
}