#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(0.8118, 0.0588, 0.0588);

    vec3 result = ambient * texture(u_texture_0, texCoord).rgb;
    gl_FragColor = vec4(result, 1.0);
}