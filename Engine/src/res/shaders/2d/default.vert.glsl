#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coord;

out vec4 color;
out vec2 texCoord;

uniform mat4 mvp;

void main()
{
   
   color = vec4(position, 0.0f, 1.0f);
   texCoord = tex_coord;
   vec4 res = mvp * vec4(position, 0.0f, 1.0f);
   gl_Position = res;
};