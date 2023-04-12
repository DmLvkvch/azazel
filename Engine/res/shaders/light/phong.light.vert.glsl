#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture_coord;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 u_mvp;
uniform mat4 u_model_matrix;
uniform mat4 u_normal_matrix;

void main()
{
    normal = vec3(u_normal_matrix * vec4(a_normal, 1.0));
    fragPos = vec3(u_model_matrix * vec4(a_position, 1.0));
    texCoord = a_texture_coord;
    gl_Position = u_mvp * vec4(a_position, 1.0);
}