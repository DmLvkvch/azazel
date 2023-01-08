#version 330 core
in vec2 texCoord;
in vec4 color;

uniform sampler2D u_texture;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, texCoord).r);
    gl_FragColor = sampled * color;
}