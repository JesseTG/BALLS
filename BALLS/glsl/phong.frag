#version 130

uniform mat4 matrix;
uniform mat4 view;

uniform vec3 LightPosition;
uniform vec3 DiffuseModelColor;
uniform vec3 SpecularModelColor;
uniform vec3 LightColor;
uniform float LightPower;
uniform float LightExponent;
uniform float AmbientScale;

vec3 TotalLight = LightColor * LightPower;
vec3 AmbientColor = DiffuseModelColor * AmbientScale;

in vec3 position_w;
in vec3 position_c;
in vec3 direction_c;
in vec3 lightDirection_c;
in vec3 lightPosition_c;
in vec3 normal_c;

out vec4 fragment;

void main(void)
{
    vec3 L = normalize(lightDirection_c);
    vec3 N = normalize(normal_c);
    vec3 E = normalize(direction_c);
    vec3 R = reflect(-L, N);

    float cosAlpha = clamp(dot(E, R), 0, 1);
    float cosTheta = clamp(dot(N, L), 0, 1);

    float len = length(lightDirection_c);
    float len2 = len * len;
    vec3 color =
        AmbientColor +
        (DiffuseModelColor * TotalLight * cosTheta) / len2 +
        (SpecularModelColor * TotalLight * cosAlpha * pow(cosAlpha, LightExponent)) / len2;

    fragment = vec4(color, 1.0);
}
