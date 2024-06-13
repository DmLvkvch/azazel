#version 450 core

layout (location = 0) in vec2 texCoord;

layout (binding = 0) uniform sampler2D u_texture_0;

layout (binding = 0) uniform UBO
{
    bool hdr;
    float exposure;
} ubo;

layout (location = 0) out vec4 frag_color;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(u_texture_0, texCoord).rgb;
    vec3 result;
    if(ubo.hdr)
    {
        // vec3 result = hdrColor / (hdrColor + vec3(1.0));
        result = vec3(1.0) - exp(-hdrColor *ubo.exposure);
        result = pow(result, vec3(1.0 / gamma));
    }
    else
    {
        result = pow(hdrColor, vec3(1.0 / gamma));
    }
    frag_color = vec4(result, 1.0);
}