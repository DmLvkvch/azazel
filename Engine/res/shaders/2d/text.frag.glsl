#version 410 core
in vec2 texCoord;
in vec4 color;

uniform sampler2D u_texture;

out vec4 frag_color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, texCoord).r);
    frag_color = sampled * color;
}