#version 450 core

layout(location = 0) in vec2 texCoord;

layout(location = 0) out vec4 frag_color;

void main()
{
   vec2 uv = texCoord;
   frag_color = vec4(mod(dot(vec2(1.0), floor(uv*15.0)), 2.0));
}