#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;
layout (location = 2) in vec3 a_normal;
out vec2 texCoord;

uniform mat4 u_mvp;

void main()
{
   texCoord = a_texture_coord;
   gl_Position = u_mvp * vec4(a_position, 1.0f);
};