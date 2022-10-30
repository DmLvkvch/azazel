#version 330 core
layout (location = 0) in vec3 positions;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    normal = mat3(transpose(inverse(model))) * normals;
    fragPos = vec3(model * vec4(positions, 1.0));
    texCoord = texCoords;
    gl_Position = mvp * vec4(positions, 1.0f);
}