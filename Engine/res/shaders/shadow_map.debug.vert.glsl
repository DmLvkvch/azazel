#version 410 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;

out vec2 texCoords;

uniform mat4 u_mvp;

void main()
{
    texCoords = a_texture_coord;
    gl_Position = u_mvp * vec4(a_position, 1.0);
}