#version 330 core

in vec2 texCoord;

uniform vec4 color;

void main()
{
    gl_FragColor = color;
}