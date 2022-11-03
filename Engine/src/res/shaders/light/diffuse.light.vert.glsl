#version 330 core
layout (location = 0) in vec3 a_positions;
layout (location = 1) in vec2 a_tex_coords;
layout (location = 2) in vec3 a_normals;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    normal = mat3(transpose(inverse(model))) * a_normals;
    fragPos = vec3(model * vec4(a_positions, 1.0));
    texCoord = a_tex_coords;
    gl_Position = mvp * vec4(a_positions, 1.0f);
}