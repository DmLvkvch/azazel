#version 450 core

layout (location = 0) in vec2 texCoord;

layout (binding = 0) uniform sampler2D u_texture_0;

layout (location = 0) out vec4 frag_color;

void main()
{
   frag_color = texture(u_texture_0, texCoord);
}