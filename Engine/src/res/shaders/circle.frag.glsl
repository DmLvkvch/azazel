#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;
uniform vec2 iResolution = vec2(1280.0, 720.0);

uniform float radius = 0.25;
uniform float t = 0.1;

void main()
{
   vec2 uv = gl_FragCoord.xy / iResolution.xy;
   uv.x *= iResolution.x / iResolution.y; 
   float d = distance(uv, vec2(0.5, 0.5));
   float col = step(d, radius);
   col *= 1.0 - step(d, radius - t);
   gl_FragColor = vec4(col, 0.0, 0.0, col);
}