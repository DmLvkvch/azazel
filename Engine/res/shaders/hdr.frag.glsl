#version 330 core
out vec4 frag_color;

in vec2 texCoord;

uniform sampler2D u_texture_0;
uniform bool hdr;
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(u_texture_0, texCoord).rgb;
    vec3 result;
    if(hdr)
    {
        // vec3 result = hdrColor / (hdrColor + vec3(1.0));
        result = vec3(1.0) - exp(-hdrColor * exposure);
        result = pow(result, vec3(1.0 / gamma));
    }
    else
    {
        result = pow(hdrColor, vec3(1.0 / gamma));
    }
    frag_color = vec4(result, 1.0);
}