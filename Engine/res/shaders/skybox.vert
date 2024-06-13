#version 450 core

layout (location = 0) in vec3 a_position;

layout (binding = 0) uniform UBO
{
    mat4 projection;
    mat4 view;
} ubo;

layout(location = 0) out vec3 texCoord;

void main()
{
    texCoord = a_position;
    vec4 position = ubo.projection * ubo.view * vec4(a_position, 1.0);
    gl_Position = position.xyww;
}  