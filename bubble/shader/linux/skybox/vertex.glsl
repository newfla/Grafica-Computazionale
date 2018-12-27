#version 320 es
precision highp float;
layout (location = 0) in vec3 aPos;
out vec3 TexCoords;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    TexCoords=aPos;
    vec4 pos = proj * view * vec4(aPos, 1.);
    gl_Position=pos.xyww;
}