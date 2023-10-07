#version 450 core

layout(location = 0) in vec3 texCoord;

layout (binding = 0) uniform samplerCube skybox;

layout(location = 0) out vec4 frag_color;

void main()
{    
    frag_color = texture(skybox, texCoord);
}