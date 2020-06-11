#version 330 core

in vec2 coord;

out vec4 outColor;

uniform sampler2D sprite;
uniform float opacity;


void main()
{
    outColor = texture(sprite, coord);
    outColor.a *= opacity;
}