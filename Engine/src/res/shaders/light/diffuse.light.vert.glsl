#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;
layout (location = 2) in vec3 a_normal;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 u_mvp;
uniform mat4 u_model;

void main()
{
    normal = mat3(transpose(inverse(model))) * a_normal;
    fragPos = vec3(u_model * vec4(a_position, 1.0));
    texCoord = a_texture_coord;
    gl_Position = u_mvp * vec4(a_position, 1.0f);
}