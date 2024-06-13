#version 450 core

layout (location = 0) in vec2 texCoord;

layout (binding = 0) uniform UBO
{
   float u_radius;
   float u_thickness;
} ubo;

layout (location = 0) out vec4 frag_color;

void main()
{
   vec2 uv = texCoord;
   float d = distance(uv, vec2(0.5, 0.5));
   float col = step(d, ubo.u_radius);
   col *= step(ubo.u_radius * (1.0 - ubo.u_thickness), d);
   frag_color = vec4(col, 0.0, 0.0, col);
}