#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture_coord;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat4 u_normalMatrix;

void main()
{
    normal = vec3(u_normalMatrix * vec4(a_normal, 1.0));
    fragPos = vec3(u_model * vec4(a_position, 1.0));
    texCoord = a_texture_coord;
    gl_Position = u_mvp * vec4(a_position, 1.0);
}