#version 450

in  vec3        vNormal;
in  vec2        vTexCoords;
out vec4        FragColor;

uniform float       time;
uniform sampler2D   albedo;

void main()
{
    //FragColor = vec4(vNormal, 1.f);
    FragColor = texture(albedo, vTexCoords);
}