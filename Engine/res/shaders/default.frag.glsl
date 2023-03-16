#version 410 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

out vec4 frag_color;

void main()
{
   frag_color = texture(u_texture_0, texCoord);
}