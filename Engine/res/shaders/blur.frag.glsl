#version 410 core
out vec4 frag_color;

in vec2 texCoord;

uniform sampler2D u_texture_0;
uniform bool hdr;
uniform float exposure;

void main()
{             
    float Pi = 6.28318530718; // Pi*2
    
    // GAUSSIAN BLUR SETTINGS {{{
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 3.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 8.0; // BLUR SIZE (Radius)
    // GAUSSIAN BLUR SETTINGS }}}
   
    vec2 Radius = vec2(0.004, 0.004);

    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = texCoord;
    // Pixel colour
    vec4 Color = texture(u_texture_0, uv);
    
    // Blur calculations
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture( u_texture_0, uv+vec2(cos(d),sin(d))*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    frag_color = Color;
}