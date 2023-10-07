#version 450 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec4 color;

layout(binding = 1) uniform sampler2D u_texture;

layout(location = 0) out vec4 frag_color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, texCoord).r);
    frag_color = sampled * color;
}