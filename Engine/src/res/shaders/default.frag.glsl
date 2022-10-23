#version 330 core

in vec4 color;

in vec2 texCoord;

uniform sampler2D texture_0;

void main()
{
   vec4 c = texture(texture_0, texCoord);
   gl_FragColor = c;
}