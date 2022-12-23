#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

void main()
{
   float s = sqrt(dot(texCoord - 0.5, texCoord - 0.5));
   if (s >= 0.5)
   {
      discard;
   }
   vec4 rgb = texture(u_texture_0, texCoord);
   gl_FragColor = vec4(rgb);
}