#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;

uniform mat4 u_mvp;

out vec2 texCoord;

void main()
{
    texCoord = a_texture_coord;
    gl_Position = u_mvp * vec4(a_position, 1.0);
}