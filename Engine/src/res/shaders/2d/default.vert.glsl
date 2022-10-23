#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coord;

out vec4 color;
out vec2 texCoord;

void main()
{
   color = vec4(position, 0.0, 1.0);
   texCoord = tex_coord;
   gl_Position = vec4(position.x, position.y, 0.0, 1.0);
};