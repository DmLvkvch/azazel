#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;
uniform vec2 u_iResolution = vec2(1280.0, 720.0); //viewport

void main()
{
   vec2 uv = gl_FragCoord.xy / u_iResolution.xx;
   gl_FragColor = vec4(mod(dot(vec2(1.0), floor(uv*15.0)), 2.0));
}