#version 130

uniform mat4 matrix;
uniform mat4 model;
uniform mat4 view;
uniform vec2 mouseCoords;

const vec3 LightPosition = vec3(0, 7, 0);


in vec3 position;
in vec3 normal;

out vec3 position_w;
out vec3 position_c;
out vec3 direction_c;
out vec3 lightDirection_c;
out vec3 lightPosition_c;
out vec3 normal_c;

void main(void)
{
    vec4 position4 = vec4(position, 1);
    gl_Position = matrix * position4;

    position_w = vec3(model * position4);

    position_c = vec3(view * model * position4);
    direction_c = -position_c;

    lightPosition_c = vec3(view * vec4(LightPosition, 1));
    lightDirection_c = direction_c + lightPosition_c;


    normal_c = vec3(view * model * vec4(normal, 0));

}
