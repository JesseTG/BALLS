#version 140

uniform mat4 matrix;

in vec3 fragPosition;
in vec3 fragNormal;

out vec4 fragment;

void main(void)
{
    fragment = vec4(fragNormal * 0.5 + 0.5, 1.0);
}
