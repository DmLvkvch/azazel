#version 330 core

in vec2 texCoord;

uniform sampler2D u_texture_0;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    gl_FragColor = vec4(result, 1.0);
}