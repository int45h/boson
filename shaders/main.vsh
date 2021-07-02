#version 450
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;
layout (location = 2) in vec2 vUV;

out vec3    vNormal;
out vec2    vTexCoords;

uniform mat4    projection,
                view,
                model;

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.f);
    vNormal     = vNor;
    vTexCoords  = vUV;
}