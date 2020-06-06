#version 330 core

in vec2 vertex;
in vec2 textureCoordinate;

out vec2 coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform int stupid;

void main()
{
    coord = textureCoordinate;
    gl_Position = projection * view * model * vec4(vertex, 0.0, 1.0);
}