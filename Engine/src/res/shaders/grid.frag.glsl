#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

void main()
{
   gl_FragColor = vec4(mod(dot(vec2(1.0), floor(texCoord*15.0)), 2.0));
}