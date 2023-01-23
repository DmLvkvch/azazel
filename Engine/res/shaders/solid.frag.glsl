#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

void main()
{
   gl_FragColor = texture(u_texture_0, texCoord);
}