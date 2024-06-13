#version 450 core

layout (location = 0) in vec2 texCoord;

layout (binding = 1) uniform sampler2D u_texture_0;
layout (binding = 0) uniform UBO
{
    uniform bool hdr;
    uniform float exposure;
} ubo;

layout (location = 0) out vec4 frag_color;

void main()
{             
    float Pi = 6.28318530718;
    
    float Directions = 16.0;
    float Quality = 3.0;
    float Size = 8.0;
   
    vec2 Radius = vec2(0.004, 0.004);

    vec2 uv = texCoord;

    vec4 Color = texture(u_texture_0, uv);
    
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture( u_texture_0, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    Color /= Quality * Directions - 15.0;
    frag_color = Color;
}