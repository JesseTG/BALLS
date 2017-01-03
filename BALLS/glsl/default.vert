#version 140

uniform mat4 matrix;

in vec3 position;
in vec3 normal;

out vec3 fragPosition;
out vec3 fragNormal;

void main(void)
{
    gl_Position = matrix * vec4(position, 1);
    fragPosition = gl_Position.xyz;
    fragNormal = normal;
}
