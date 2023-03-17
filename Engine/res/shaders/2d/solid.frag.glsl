#version 410 core

in vec2 texCoord;

uniform vec4 color;

out vec4 frag_color;

void main()
{
    frag_color = color;
}