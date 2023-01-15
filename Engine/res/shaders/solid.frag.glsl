#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture;

void main()
{
   gl_FragColor = texture(u_texture, texCoord);
}