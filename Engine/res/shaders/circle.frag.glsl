#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;
uniform vec2 iResolution = vec2(1280.0, 720.0);

uniform float radius = 0.25;
uniform float thickness = 0.1;

void main()
{
   vec2 uv = texCoord;
   float d = distance(uv, vec2(0.5, 0.5));
   float col = step(d, radius);
   col *= step(radius * (1.0 - thickness), d);
   gl_FragColor = vec4(col, 0.0, 0.0, col);
}

//#version 330 core
//
//in vec2 texCoord;
//
//uniform sampler2D u_texture_0;
//uniform vec2 iResolution = vec2(1280.0, 720.0);
//
//uniform float radius = 0.25;
//uniform float thickness = 0.1;
//
//void main()
//{
//   vec2 uv = texCoord;
//   float d = radius - length(uv);
//   float fade = 0.005;
//   float col = smoothstep(0.0, fade, d);
//   col *= smoothstep(thickness, thickness - fade, d);
//   gl_FragColor = vec4(col, 0.0, 0.0, col);
//}