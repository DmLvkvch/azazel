#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;
layout (location = 2) in vec3 a_normal;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 u_mvp;
uniform mat4 u_model;

uniform vec2 offsets[5];

void main()
{
    vec2 offset = offsets[gl_InstanceID];
    vec3 pos = a_position;
    pos.z += offset.x;
    normal = mat3(transpose(inverse(u_model))) * a_normal;
    fragPos = vec3(u_model * vec4(pos, 1.0));
    texCoord = a_texture_coord;
    vec4 resPos = u_mvp * vec4(pos, 1.0f);
    gl_Position = resPos;
}