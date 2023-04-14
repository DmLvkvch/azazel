#version 410 core

layout (location = 0) in vec3 a_position;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    texCoords = a_position;
    vec4 position = projection * view * vec4(a_position, 1.0);
    gl_Position = position.xyww;
}  