#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;

layout(binding = 0)  uniform UBO
{
    uniform mat4 u_mvp;
} ubo;

layout(location = 0) out vec2 texCoord;

void main()
{
    texCoord = a_texture_coord;
    gl_Position = ubo.u_mvp * vec4(a_position, 1.0);
}