#version 450 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_texture_coord;

layout (binding = 0) uniform UBO 
{
	mat4 u_mvp;
} ubo;

layout(location = 0) out vec2 texCoord;
layout(location = 1) out vec4 color;

void main()
{
    texCoord = a_texture_coord;
    color = vec4(0.102, 0.8745, 0.7961, 1.0);
    gl_Position = ubo.u_mvp * vec4(a_position, 0.0, 1.0);
}