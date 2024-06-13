#version 450 core

layout (location = 0) in vec3 a_position;

layout(binding = 0) uniform UBO
{
    mat4 lightSpaceMatrix;
    mat4 model;
} ubo;

void main()
{
    gl_Position = ubo.lightSpaceMatrix * ubo.model * vec4(a_position, 1.0);
}