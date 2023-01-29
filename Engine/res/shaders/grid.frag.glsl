#version 330 core

in vec2 texCoord;

void main()
{
   vec2 uv = texCoord;
   gl_FragColor = vec4(mod(dot(vec2(1.0), floor(uv*15.0)), 2.0));
}