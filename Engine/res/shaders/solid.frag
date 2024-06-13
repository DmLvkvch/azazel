#version 450 core

layout(location = 0) in vec2 texCoord;

layout (binding = 0) uniform UBO
{
    vec4 color;
} ubo;

layout(location = 0) out vec4 frag_color;

void main()
{
    frag_color = ubo.color;
}