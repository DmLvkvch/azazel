#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture_coord;

layout (binding = 0) uniform UBO
{
    mat4 u_mvp;
    mat4 u_model_matrix;
    mat4 u_normal_matrix;
} ubo;

layout(location = 0) out vec3 normal;
layout(location = 1) out vec3 fragPos;
layout(location = 2) out vec2 texCoord;

void main()
{
    normal = vec3(ubo.u_normal_matrix * vec4(a_normal, 1.0));
    fragPos = vec3(ubo.u_model_matrix * vec4(a_position, 1.0));
    texCoord = a_texture_coord;
    gl_Position = ubo.u_mvp * vec4(a_position, 1.0);
}