#version 330 core

in vec2 coord;

out vec4 outColor;

uniform sampler2D sprite;

float framecount = 2;
uniform float frame;
uniform int stupid;

void main()
{
    vec2 coordNEW = coord;
    if (stupid == 1)
    {
        //coordNEW.y = coord.y / framecount;
        //coordNEW.y = coordNEW.y + (1.0 / framecount) * frame;
    }

    outColor = texture(sprite, coordNEW);
}